/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 20:36:42 by amounadi         ###   ########.fr       */
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
    list_directories(paths,&flags);
    free_paths(paths);
    return (0);
}