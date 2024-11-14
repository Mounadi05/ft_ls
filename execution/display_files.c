/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <amounadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:30:35 by amounadi          #+#    #+#             */
/*   Updated: 2024/11/14 23:05:18 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	display_file_info(t_file *file, t_flags *flags, t_padding *pad)
{
	char			*time_str;
	struct passwd	*pw;
	struct group	*gr;
	char			link_target[1024];
	ssize_t			link_len;

	display_file_type_permission(file);

	// Number of hard links with padding
	size_t	i;
	int		tmp;
	size_t	count_len;

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

	// User and group name with padding
	pw = getpwuid(file->stats.st_uid);
	gr = getgrgid(file->stats.st_gid);
	if (!flags->g)
	{
		ft_printf(" %s", pw->pw_name);
		i = 0;
		while (i++ < pad->user_width - ft_strlen(pw->pw_name))
			ft_printf(" ");
	}
	ft_printf(" %s", gr->gr_name);
	i = 0;
	while (i++ < pad->group_width - ft_strlen(gr->gr_name))
		ft_printf(" ");

	// File size with padding
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

	// Modification time
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

