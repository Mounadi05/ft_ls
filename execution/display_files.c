#include "../includes/ft_ls.h"

void display_file_info(t_file *file)
{
    char *time_str;
    struct passwd *pw;
    struct group *gr;

  
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

    ft_printf(" %s\n", file->name);
    
}

void display_files(t_file *files, t_flags *flags)
{
    sort_files(&files, flags);
    if (flags->l && 0)
    {
        // Display detailed information
        t_file *current = files;
        while (current)
        {
            display_file_info(current);
            current = current->next;
        }
    }
    else
    {
        // Display files in columns
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int term_width = w.ws_col; 

        // Collect file names and calculate total length
        int file_count = 0;
        int max_len = 0; 
        t_file *current = files;
        while (current)
        {
            int len = ft_strlen(current->name);
            if (len > max_len)
                max_len = len;
            file_count++;
            current = current->next;
        }

        // Calculate number of columns
        int cols = term_width / (max_len + 2);
        if (cols == 0)
            cols = 1;  // Ensure at least 1 column
        int rows = (file_count + cols - 1) / cols;  // Round up for rows

        // Collect file names
        current = files;
        char **file_names = (char **)malloc(file_count * sizeof(char *));
        int i = 0;
        while (current)
        {
            file_names[i++] = current->name;
            current = current->next;
        }

        // Print files in columns
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                int index = col * rows + row;
                if (index < file_count)
                {
                    ft_putstr(file_names[index]);
                    int padding = max_len - ft_strlen(file_names[index]) + 2; 
                    while (padding-- > 0)
                        ft_putchar(' ');
                }
            }
            ft_putchar('\n');
        }

        free(file_names);
    }
}