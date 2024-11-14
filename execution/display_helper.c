/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:44:46 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 23:02:08 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	display_files(t_file *files, t_flags *flags)
{
	if (!flags->f)
		sort_files(&files, flags);
	if ((flags->l || flags->g) && !flags->f)
		display_long_format(files, flags);
	else
		display_regular_format(files, flags);
}

void	display_regular_format(t_file *files, t_flags *flags)
{
	int			file_count;
	int			max_len;
	t_display	display;

	if (flags->f && !flags->d)
		files = ft_reverse(files);
	file_count = get_file_count_and_max_len(files, &max_len);
	display.term_width = get_terminal_width();
	display.file_names = collect_file_names(files, file_count);
	display.cols = calculate_optimal_columns(file_count, display.file_names,
			display.term_width);
	if (display.cols == 0)
		display.cols = 1;
	display.rows = (file_count + display.cols - 1) / display.cols;
	display.col_widths = (int *)ft_calloc(display.cols, sizeof(int));
	calculate_column_width(display.col_widths, display.file_names, file_count,
		display.cols);
	print_filenames(&display, file_count);
	free(display.col_widths);
	free(display.file_names);
}

int	get_file_count_and_max_len(t_file *files, int *max_len)
{
	int		file_count;
	int		len;
	t_file	*current;

	*max_len = 0;
	file_count = 0;
	current = files;
	while (current)
	{
		len = ft_strlen(current->name);
		if (len > *max_len)
			*max_len = len;
		file_count++;
		current = current->next;
	}
	return (file_count);
}

char	**collect_file_names(t_file *files, int file_count)
{
	char	**file_names;
	t_file	*current;
	int		i;

	file_names = (char **)malloc(file_count * sizeof(char *));
	current = files;
	i = 0;
	while (current)
	{
		file_names[i] = current->name;
		i++;
		current = current->next;
	}
	return (file_names);
}

void	print_filenames(t_display *display, int file_count)
{
	int	row;
	int	col;
	int	index;
	int	padding;

	row = 0;
	while (row < display->rows)
	{
		col = 0;
		while (col < display->cols)
		{
			index = row + col * display->rows;
			if (index < file_count)
			{
				ft_putstr(display->file_names[index]);
				padding = display->col_widths[col]
					- ft_strlen(display->file_names[index]) + 2;
				while (padding-- > 0)
					ft_putchar(' ');
			}
			col++;
		}
		ft_putchar('\n');
		row++;
	}
}
