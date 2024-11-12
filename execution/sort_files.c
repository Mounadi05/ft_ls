#include "../includes/ft_ls.h"

void swap(t_file *a, t_file *b)
{
    char *temp_name = a->name;
    char *temp_path = a->path;
    struct stat temp_stats = a->stats;

    a->name = b->name;
    a->path = b->path;
    a->stats = b->stats;

    b->name = temp_name;
    b->path = temp_path;
    b->stats = temp_stats;
}

void sort_files(t_file **files, t_flags *flags)
{

    (void) flags;
    t_file *current;
    t_file *next;

    if (!files || !*files)
        return;

    int swapped;
    do
    {
        swapped = 0;
        current = *files;
        while (current->next)
        {
            next = current->next;
            if (ft_strcasecmp(current->name, next->name) > 0)
            {
                swap(current, next);
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}





