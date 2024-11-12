#include "../includes/ft_ls.h"

void list_directories(t_paths *paths, t_flags *flags)
{
    int i;

    i = 0;
    while (i < paths->count)
        list_directory(paths->items[i++], flags, paths);
}

void list_directory(char *path, t_flags *flags, t_paths *paths)
{
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
        if (!flags->a && entry->d_name[0] == '.')
            continue;

        new_file = (t_file *)malloc(sizeof(t_file));
        if (!new_file)
        {
            ft_printf("ft_ls: memory allocation error\n");
            closedir(dir);
            return;
        }

        new_file->name = ft_strdup(entry->d_name);
        new_file->path = ft_strjoin(path, "/");
        new_file->path = ft_strjoin(new_file->path, entry->d_name);
        if (stat(new_file->path, &new_file->stats) == -1)
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
    if (paths->count > 1)
    {
        ft_printf("%s:\n", path);
    }
    display_files(files, flags);

    while (files)
    {
        t_file *tmp = files;
        files = files->next;
        free(tmp->name);
        free(tmp->path);
        free(tmp);
    }
}