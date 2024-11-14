/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:30:30 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 19:44:50 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void list_directories(t_paths *paths, t_flags *flags)
{
    int i;
    int new_line;
    
    i = 0;
    new_line = 0;
    while (i < paths->count)
    {
        list_directory(paths->items[i++], flags, paths,0,new_line);
        new_line = 1;
    }
}

void get_subdirectories(t_paths *paths, t_file *files, t_flags *flags)
{
    t_file *current = files;
    while (current)
    {
        if (S_ISDIR(current->stats.st_mode) &&
            ft_strcmp(current->name, ".") != 0 &&
            ft_strcmp(current->name, "..") != 0)
            list_directory(current->path, flags, paths,1,1);
        current = current->next;
    }
}

void list_directory(char *path, t_flags *flags, t_paths *paths, int is_recursive, int new_line)
{
    // If -d flag is set, treat the directory as a file
    if (flags->d)
    {
        t_file *dir_entry = (t_file *)malloc(sizeof(t_file));
        if (!dir_entry)
            return;
            
        dir_entry->name = ft_strdup(path);
        dir_entry->path = ft_strdup(path);
        if (stat(path, &dir_entry->stats) == -1)
        {
            ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
            free(dir_entry->name);
            free(dir_entry->path);
            free(dir_entry);
            return;
        }
        dir_entry->next = NULL;
        display_files(dir_entry, flags);
        
        free(dir_entry->name);
        free(dir_entry->path);
        free(dir_entry);
        return;
    }

    DIR *dir;
    struct dirent *entry;
    t_file *files = NULL;
    t_file *new_file;

    dir = opendir(path);
    if (!dir)
    {
        ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (!flags->f && !flags->a && entry->d_name[0] == '.')
            continue;
        new_file = (t_file *)malloc(sizeof(t_file));
        if (!new_file)
        {
            ft_printf("ft_ls: memory allocation error\n");
            closedir(dir);
            return;
        }

        new_file->name = ft_strdup(entry->d_name);
        size_t path_len = ft_strlen(path);
        if(path[path_len - 1] != '/')
            new_file->path = ft_strjoin(path, "/");
        else
            new_file->path = ft_strdup(path);
        new_file->path = ft_strjoin(new_file->path, entry->d_name);
        
        // Change stat to lstat to detect symbolic links
        if (lstat(new_file->path, &new_file->stats) == -1)
        {
            ft_printf("ft_ls: cannot access '%s': %s\n", new_file->path, strerror(errno));
            free(new_file->name);
            free(new_file->path);
            free(new_file);
            continue;
        }

        new_file->next = files;
        files = new_file;
    }
    closedir(dir);

    // sort_files(&files, flags);
    if (new_line)
        ft_putchar('\n');
    if (paths->count > 1 || is_recursive)
        ft_printf("%s:\n", path);
    display_files(files, flags);
    if (flags->cap_R)
        get_subdirectories(paths, files, flags);
    while (files)
    {
        t_file *tmp = files;
        files = files->next;
        free(tmp->name);
        free(tmp->path);
        free(tmp);
    }
}