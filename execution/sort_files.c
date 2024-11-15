/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:03:13 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/15 21:38:54 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

long	compare_by_time(t_file *a, t_file *b)
{
	long	cmp;

	cmp = 0;
	if (a->stats.st_mtime != b->stats.st_mtime)
		cmp = b->stats.st_mtime - a->stats.st_mtime;
	else if (a->stats.st_mtim.tv_nsec != b->stats.st_mtim.tv_nsec)
		cmp = b->stats.st_mtim.tv_nsec - a->stats.st_mtim.tv_nsec;
	else
		cmp = ft_strcasecmp(a->name, b->name);
	return (cmp);
}

int	compare_files(t_file *a, t_file *b, t_flags *flags)
{
	long	cmp;

	cmp = 0;
	if (flags->u)
	{
		if (a->stats.st_atime != b->stats.st_atime)
			cmp = b->stats.st_atime - a->stats.st_atime;
		else if (a->stats.st_atim.tv_nsec != b->stats.st_atim.tv_nsec)
			cmp = b->stats.st_atim.tv_nsec - a->stats.st_atim.tv_nsec;
		else
			cmp = ft_strcasecmp(b->name, a->name);
	}
	else if (flags->t)
		cmp = compare_by_time(a, b);
	else
		cmp = ft_strcasecmp(a->name, b->name);
	if (flags->r && !flags->f)
		return (-cmp);
	return (cmp);
}

void	swap(t_file *a, t_file *b)
{
	char		*temp_name;
	char		*temp_path;
	struct stat	temp_stats;

	temp_name = a->name;
	temp_path = a->path;
	temp_stats = a->stats;
	a->name = b->name;
	a->path = b->path;
	a->stats = b->stats;
	b->name = temp_name;
	b->path = temp_path;
	b->stats = temp_stats;
}

void	sort_files(t_file **files, t_flags *flags)
{
	t_file	*current;
	t_file	*next;
	int		swapped;

	if (flags->f || !files || !*files)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *files;
		while (current->next)
		{
			next = current->next;
			if (compare_files(current, next, flags) > 0)
			{
				swap(current, next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}
