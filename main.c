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

int main(int argc, char **argv)
{
    t_flags flags;
    int file_indices[argc];
    int file_count;
    t_paths *paths;

    file_count = parse_flags(argc, argv, &flags, file_indices);
    if (file_count == -1)
        return (1);

    paths = parse_arguments(argc, argv, file_indices, file_count);
    if (!paths)
        return (1);

    // Debug print paths
    // for (int i = 0; i < paths->count; i++)
    //     ft_printf("Path %d: %s\n", i, paths->items[i]);
    // ft_printf("Flags parsed successfully.\n");
	// ft_printf("flags:\n");
	// ft_printf("l: %d\n", flags.l);
	// ft_printf("r: %d\n", flags.r);
	// ft_printf("a: %d\n", flags.a);
	// ft_printf("R: %d\n", flags.cap_R);
	// ft_printf("t: %d\n", flags.t);
	// ft_printf("u: %d\n", flags.u);
	// ft_printf("f: %d\n", flags.f);
	// ft_printf("g: %d\n", flags.g);
	// ft_printf("d: %d\n", flags.d);
	// ft_printf("G: %d\n", flags.cap_G);
    list_directories(paths,&flags);
    free_paths(paths);
    return (0);
}