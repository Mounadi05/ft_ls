/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_helper3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:03:31 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/15 23:03:51 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	display_long_format(t_file *files, t_flags *flags)
{
	t_padding	pad;
	t_file		*current;

	calculate_padding(files, &pad);
	ft_printf("total %d\n", calculate_total_blocks(files) / 2);
	current = files;
	while (current)
	{
		display_file_info(current, flags, &pad);
		current = current->next;
	}
}
