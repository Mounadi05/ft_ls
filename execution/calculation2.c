/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:02:35 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 23:01:34 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	calculate_total_width(int cols, int file_count, char **file_names)
{
	int	*col_widths;
	int	total_width;
	int	col;

	col_widths = (int *)ft_calloc(cols, sizeof(int));
	calculate_column_width(col_widths, file_names, file_count, cols);
	total_width = -2;
	col = 0;
	while (col < cols)
	{
		total_width += col_widths[col] + 2;
		col++;
	}
	free(col_widths);
	return (total_width);
}

void	calculate_column_width(int *col_widths, char **file_names,
			int file_count, int cols)
{
	int		col;
	int		row;
	int		index;
	int		rows;
	size_t	max_col_width;

	rows = (file_count + cols - 1) / cols;
	col = 0;
	while (col < cols)
	{
		max_col_width = 0;
		row = 0;
		while (row < rows)
		{
			index = col * rows + row;
			if (index < file_count)
			{
				if (ft_strlen(file_names[index]) > max_col_width)
					max_col_width = ft_strlen(file_names[index]);
			}
			row++;
		}
		col_widths[col] = max_col_width;
		col++;
	}
}

size_t	calculate_number_length(size_t number)
{
	size_t	len;

	len = 1;
	while (number >= 10)
	{
		number /= 10;
		len++;
	}
	return (len);
}
