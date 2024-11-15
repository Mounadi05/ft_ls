/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:02:35 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/15 23:44:53 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	calculate_total_width(int cols, int file_count, char **f_n)
{
	int	*col_widths;
	int	total_width;
	int	col;

	col_widths = (int *)ft_calloc(cols, sizeof(int));
	calculate_column_width(col_widths, f_n, file_count, cols);
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

void	calculate_column_width(int *c_w, char **f_n, int f_c, int cols)
{
	int		col;
	int		row;
	int		index;
	int		rows;
	size_t	max_col_width;

	rows = (f_c + cols - 1) / cols;
	col = 0;
	while (col < cols)
	{
		max_col_width = 0;
		row = 0;
		while (row < rows)
		{
			index = col * rows + row;
			if (index < f_c)
			{
				if (ft_strlen(f_n[index]) > max_col_width)
					max_col_width = ft_strlen(f_n[index]);
			}
			row++;
		}
		c_w[col] = max_col_width;
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
