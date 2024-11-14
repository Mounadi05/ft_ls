/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:50:15 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 23:01:34 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	initialize_padding(t_padding *pad)
{
	pad->link_width = 0;
	pad->user_width = 0;
	pad->group_width = 0;
	pad->size_width = 0;
}

void	update_padding(t_file *file, t_padding *pad)
{
	struct passwd	*pw;
	struct group	*gr;
	size_t			link_len;
	size_t			size_len;

	pw = getpwuid(file->stats.st_uid);
	gr = getgrgid(file->stats.st_gid);
	link_len = calculate_number_length(file->stats.st_nlink);
	size_len = calculate_number_length(file->stats.st_size);
	if (link_len > pad->link_width)
		pad->link_width = link_len;
	if (ft_strlen(pw->pw_name) > pad->user_width)
		pad->user_width = ft_strlen(pw->pw_name);
	if (ft_strlen(gr->gr_name) > pad->group_width)
		pad->group_width = ft_strlen(gr->gr_name);
	if (size_len > pad->size_width)
		pad->size_width = size_len;
}

int	calculate_optimal_columns(int file_count, char **file_names,
			int term_width)
{
	int	cols;
	int	total_width;

	cols = 1;
	while (cols <= file_count)
	{
		total_width = calculate_total_width(cols, file_count,
				file_names);
		if (total_width > term_width)
			return (cols - 1);
		cols++;
	}
	return (cols - 1);
}

int	calculate_total_blocks(t_file *files)
{
	t_file	*current;
	int		total;

	current = files;
	total = 0;
	while (current)
	{
		total += current->stats.st_blocks;
		current = current->next;
	}
	return (total);
}

void	calculate_padding(t_file *files, t_padding *pad)
{
	t_file	*current;

	current = files;
	initialize_padding(pad);
	while (current)
	{
		update_padding(current, pad);
		current = current->next;
	}
}
