/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by amounadi          #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	main(int argc, char **argv)
{
	t_flags	flags;
	int		start_index;
	t_paths	*paths;

	start_index = parse_flags(argc, argv, &flags);
	if (start_index == -1)
		return (1);
	paths = parse_arguments(argc, argv, start_index);
	if (!paths)
		return (1);
	// Debug print paths
	for (int i = 0; i < paths->count; i++)
		ft_printf("Path %d: %s\n", i, paths->items[i]);
	free_paths(paths);
	return (0);
}