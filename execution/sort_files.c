/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:03:13 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 23:03:36 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <stddef.h>
#include <wchar.h>

int compare_files(t_file *a, t_file *b, t_flags *flags)
{
    long cmp = 0;
    if (flags->f)
        return 0;
    if (flags->t)
    {
        if ( a->stats.st_mtime != b->stats.st_mtime)
            cmp = a->stats.st_mtime - b->stats.st_mtime;
        else if (a->stats.st_mtim.tv_nsec != b->stats.st_mtim.tv_nsec)
            cmp = a->stats.st_mtim.tv_nsec - b->stats.st_mtim.tv_nsec;
        else
        {
            cmp = ft_strcasecmp(a->name, b->name);
            cmp = -cmp;
        }
    }
    else
    {
        cmp = ft_strcasecmp(a->name, b->name);
    }
    if (flags->r && !flags->f)
        return -cmp;
    return cmp;
}

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
    if (flags->f) 
        return;

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
            if (compare_files(current, next,flags) > 0)
            {
                swap(current, next);
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}





