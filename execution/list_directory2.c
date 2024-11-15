/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_directory2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:16:53 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/15 23:38:28 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	list_directories(t_paths *paths, t_flags *flags)
{
	int	i;
	int	*new_line;

	i = 0;
	new_line = malloc(sizeof(int) * 2);
	new_line[0] = 0;
	new_line[1] = 0;
	while (i < paths->count)
	{
		list_directory(paths->items[i++], flags, paths, new_line);
		new_line[0] = 1;
	}
	free(new_line);
}

void	get_subdirectories(t_paths *paths, t_file *files, t_flags *flags)
{
	t_file	*current;
	int		*new_line;

	current = files;
	new_line = malloc(sizeof(int) * 2);
	new_line[0] = 1;
	new_line[1] = 1;
	while (current)
	{
		if (S_ISDIR(current->stats.st_mode)
			&& ft_strcmp(current->name, ".") != 0
			&& ft_strcmp(current->name, "..") != 0)
			list_directory(current->path, flags, paths, new_line);
		current = current->next;
	}
	free(new_line);
}
