
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by amounadi          #+#    #+#            */
/*   Updated: 2023/01/01 00:00:00 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_paths	*parse_arguments(int argc, char **argv, int start_index)
{
	t_paths	*paths;
	int		i;
	int		j;

	paths = (t_paths *)malloc(sizeof(t_paths));
	if (!paths)
		return (NULL);
	paths->count = argc - start_index;
	if (paths->count == 0)
	{
		paths->items = (char **)malloc(sizeof(char *));
		paths->items[0] = ft_strdup(".");
		paths->count = 1;
		return (paths);
	}
	paths->items = (char **)malloc(sizeof(char *) * paths->count);
	if (!paths->items)
	{
		free(paths);
		return (NULL);
	}
	i = start_index;
	j = 0;
	while (i < argc)
		paths->items[j++] = ft_strdup(argv[i++]);
	return (paths);
}

void	free_paths(t_paths *paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (i < paths->count)
		free(paths->items[i++]);
	free(paths->items);
	free(paths);
}