#include "../includes/ft_ls.h"

void display_file_info(t_file *file, t_flags *flags)
{
    char *time_str;
    struct passwd *pw;
    struct group *gr;

    if (flags->l)
    {
        // File type and permissions
        ft_printf((S_ISDIR(file->stats.st_mode)) ? "d" : "-");
        ft_printf((file->stats.st_mode & S_IRUSR) ? "r" : "-");
        ft_printf((file->stats.st_mode & S_IWUSR) ? "w" : "-");
        ft_printf((file->stats.st_mode & S_IXUSR) ? "x" : "-");
        ft_printf((file->stats.st_mode & S_IRGRP) ? "r" : "-");
        ft_printf((file->stats.st_mode & S_IWGRP) ? "w" : "-");
        ft_printf((file->stats.st_mode & S_IXGRP) ? "x" : "-");
        ft_printf((file->stats.st_mode & S_IROTH) ? "r" : "-");
        ft_printf((file->stats.st_mode & S_IWOTH) ? "w" : "-");
        ft_printf((file->stats.st_mode & S_IXOTH) ? "x" : "-");

        // Number of hard links
        ft_printf(" %2ld", file->stats.st_nlink);

        // User and group name
        pw = getpwuid(file->stats.st_uid);
        gr = getgrgid(file->stats.st_gid);
        ft_printf(" %s %s", pw->pw_name, gr->gr_name);

        // File size
        ft_printf(" %5lld", (long long)file->stats.st_size);

        // Modification time
        time_str = ctime(&file->stats.st_mtime);
        time_str[16] = '\0'; // Remove the newline character
        ft_printf(" %s", time_str + 4);

        // File name
        ft_printf(" %s\n", file->name);
    }
    else
    {
        ft_printf("%s\n", file->name);
    }
}

void display_files(t_file *files, t_flags *flags)
{
    t_file *current = files;

    while (current)
    {
        display_file_info(current, flags);
        current = current->next;
    }
}