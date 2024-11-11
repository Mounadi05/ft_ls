/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by amounadi          #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>
# include <errno.h>

typedef struct s_flags
{
	int	l;
	int	r;
	int	a;
	int	t;
	int	cap_R;
	int	f;
    int u;
	int	g;
	int	d;
    int cap_G;
}	t_flags;

typedef struct s_file
{
	char			*name;
	char			*path;
	struct stat		stats;
	struct s_file	*next;
}	t_file;

typedef struct s_paths
{
	char			**items;
	int				count;
}	t_paths;

/* Parsing functions */
int		parse_flags(int argc, char **argv, t_flags *flags);
t_paths	*parse_arguments(int argc, char **argv, int start_index);
void	free_paths(t_paths *paths);
t_file	*parse_path(char *path);

/* Execution functions */
void	list_directory(char *path, t_flags *flags);
void	sort_files(t_file **files, t_flags *flags);
void	display_files(t_file *files, t_flags *flags);

#endif