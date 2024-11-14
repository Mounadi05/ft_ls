/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:30:20 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/13 19:30:21 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"

t_paths	*parse_arguments(int argc, char **argv, int *file_indices, int file_count)
{
	t_paths	*paths;
	int		i;
	(void) argc;
	paths = (t_paths *)malloc(sizeof(t_paths));
	if (!paths)
		return (NULL);
	paths->count = file_count;
	if (paths->count == 0)
    {
        paths->items = (char **)malloc(sizeof(char *));
        if (!paths->items)
        {
            free(paths);
            return (NULL);
        }
        paths->items[0] = ft_strdup(".");
        if (!paths->items[0])
        {
            free(paths->items);
            free(paths);
            return (NULL);
        }
        paths->count = 1;
        return (paths);
    }
    paths->items = (char **)malloc(sizeof(char *) * paths->count);
    if (!paths->items)
    {
        free(paths);
        return (NULL);
    }
    for (i = 0; i < file_count; i++)
    {
        paths->items[i] = ft_strdup(argv[file_indices[i]]);
        if (!paths->items[i])
        {
            while (i > 0)
                free(paths->items[--i]);
            free(paths->items);
            free(paths);
            return (NULL);
        }
    }
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