/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:30:35 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/15 23:10:16 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	display_file_permissions_and_links(t_file *file, t_padding *pad)
{
	size_t	i;
	int		tmp;
	size_t	count_len;

	display_file_type_permission(file);
	i = 0;
	tmp = file->stats.st_nlink;
	count_len = 0;
	while (tmp > 0)
	{
		count_len++;
		tmp /= 10;
	}
	ft_printf(" ");
	while (i++ < pad->link_width - count_len)
		ft_printf(" ");
	ft_printf("%d", (int)file->stats.st_nlink);
}

void	display_file_user_group(t_file *file, t_flags *flags, t_padding *pad)
{
	struct passwd	*pw;
	struct group	*gr;
	size_t			i;

	pw = getpwuid(file->stats.st_uid);
	gr = getgrgid(file->stats.st_gid);
	i = 0;
	if (!flags->g)
	{
		ft_printf(" %s", pw->pw_name);
		while (i++ < pad->user_width - ft_strlen(pw->pw_name))
			ft_printf(" ");
	}
	ft_printf(" %s", gr->gr_name);
	i = 0;
	while (i++ < pad->group_width - ft_strlen(gr->gr_name))
		ft_printf(" ");
}

void	display_file_time_name_and_link(t_file *file)
{
	char	*time_str;
	char	link_target[1024];
	ssize_t	link_len;

	time_str = ctime(&file->stats.st_mtime);
	time_str[16] = '\0';
	ft_printf(" %s", time_str + 4);
	ft_printf(" %s", file->name);
	if (S_ISLNK(file->stats.st_mode))
	{
		link_len = readlink(file->path, link_target, sizeof(link_target) - 1);
		if (link_len > 0)
		{
			link_target[link_len] = '\0';
			ft_printf(" -> %s", link_target);
		}
	}
	ft_printf("\n");
}

void	display_file_size(t_file *file, t_padding *pad)
{
	size_t	i;
	int		tmp;
	size_t	count_len;

	i = 0;
	tmp = file->stats.st_size;
	count_len = 0;
	while (tmp > 0)
	{
		count_len++;
		tmp /= 10;
	}
	if (file->stats.st_size == 0)
		count_len = 1;
	ft_printf(" ");
	while (i++ < pad->size_width - count_len)
		ft_printf(" ");
	ft_printf("%d", (int)file->stats.st_size);
	display_file_time_name_and_link(file);
}

void	display_file_info(t_file *file, t_flags *flags, t_padding *pad)
{
	display_file_permissions_and_links(file, pad);
	display_file_user_group(file, flags, pad);
	display_file_size(file, pad);
}
