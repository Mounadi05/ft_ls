/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:12:19 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/15 23:23:07 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

t_file	*ft_reverse(t_file *head)
{
	t_file	*prev;
	t_file	*current;
	t_file	*next;

	prev = NULL;
	current = head;
	next = NULL;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

int	get_terminal_width(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col == 0)
		return (80);
	else
		return (w.ws_col);
}
