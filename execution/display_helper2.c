/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_helper2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:33:44 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 23:02:36 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	display_file_type(t_file *file)
{
	if (S_ISLNK(file->stats.st_mode))
		ft_printf("l");
	else if (S_ISDIR(file->stats.st_mode))
		ft_printf("d");
	else
		ft_printf("-");
}

void	display_user_permissions(mode_t mode)
{
	if (mode & S_IRUSR)
		ft_printf("r");
	else
		ft_printf("-");
	if (mode & S_IWUSR)
		ft_printf("w");
	else
		ft_printf("-");
	if (mode & S_IXUSR)
		ft_printf("x");
	else
		ft_printf("-");
}

void	display_group_permissions(mode_t mode)
{
	if (mode & S_IRGRP)
		ft_printf("r");
	else
		ft_printf("-");
	if (mode & S_IWGRP)
		ft_printf("w");
	else
		ft_printf("-");
	if (mode & S_IXGRP)
		ft_printf("x");
	else
		ft_printf("-");
}

void	display_other_permissions(mode_t mode)
{
	if (mode & S_IROTH)
		ft_printf("r");
	else
		ft_printf("-");
	if (mode & S_IWOTH)
		ft_printf("w");
	else
		ft_printf("-");
	if (mode & S_IXOTH)
		ft_printf("x");
	else
		ft_printf("-");
}

void	display_file_type_permission(t_file *file)
{
	display_file_type(file);
	display_user_permissions(file->stats.st_mode);
	display_group_permissions(file->stats.st_mode);
	display_other_permissions(file->stats.st_mode);
}
