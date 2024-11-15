/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:30:30 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/15 23:46:48 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	handle_directory_as_file(char *path, t_flags *flags)
{
	t_file	*dir_entry;

	dir_entry = (t_file *)malloc(sizeof(t_file));
	if (!dir_entry)
		return ;
	dir_entry->name = ft_strdup(path);
	dir_entry->path = ft_strdup(path);
	if (stat(path, &dir_entry->stats) == -1)
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		free(dir_entry->name);
		free(dir_entry->path);
		free(dir_entry);
		return ;
	}
	dir_entry->next = NULL;
	display_files(dir_entry, flags);
	free(dir_entry->name);
	free(dir_entry->path);
	free(dir_entry);
}

void	handle_error(t_file *new_file)
{
	ft_printf("ft_ls: cannot access '%s': %s\n",
		new_file->path, strerror(errno));
	free(new_file->name);
	free(new_file->path);
	free(new_file);
}

void	process_directory_entry(char *path, struct dirent *entry,
	t_file **files, t_flags *flags)
{
	t_file	*new_file;
	size_t	path_len;

	if (!flags->f && !flags->a && entry->d_name[0] == '.')
		return ;
	new_file = (t_file *)malloc(sizeof(t_file));
	if (!new_file)
	{
		ft_printf("ft_ls: memory allocation error\n");
		return ;
	}
	new_file->name = ft_strdup(entry->d_name);
	path_len = ft_strlen(path);
	if (path[path_len - 1] != '/')
		new_file->path = ft_strjoin(path, "/");
	else
		new_file->path = ft_strdup(path);
	new_file->path = ft_strjoin(new_file->path, entry->d_name);
	if (lstat(new_file->path, &new_file->stats) == -1)
	{
		handle_error(new_file);
		return ;
	}
	new_file->next = *files;
	*files = new_file;
}

void	read_directory(char *path, t_flags *flags, t_file **files)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (!dir)
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		process_directory_entry(path, entry, files, flags);
		entry = readdir(dir);
	}
	closedir(dir);
}

void	list_directory(char *path, t_flags *flags, t_paths *paths, int *re_nl)
{
	t_file	*files;
	t_file *tmp;

	if (flags->d)
		return (handle_directory_as_file(path, flags));
	files = NULL;
	read_directory(path, flags, &files);
	if (re_nl[0])
		ft_putchar('\n');
	if (paths->count > 1 || re_nl[1])
		ft_printf("%s:\n", path);
	display_files(files, flags);
	if (flags->cap_r)
		get_subdirectories(paths, files, flags);
	while (files)
	{        
        tmp = files;
		files = files->next;
		free(tmp->name);
		free(tmp->path);
		free(tmp);
	}
}