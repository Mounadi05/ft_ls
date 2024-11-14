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
#include <string.h>
#include <sys/ioctl.h>
#include <locale.h>

// structs
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

typedef struct s_padding
{
    size_t link_width;
    size_t user_width;
    size_t group_width;
    size_t size_width;
} t_padding;

typedef struct s_display
{
	char	**file_names;
	int		*col_widths;
	int		cols;
	int		rows;
	int		term_width;
}				t_display;

/* Parsing functions */
int	parse_flags(int argc, char **argv, t_flags *flags, int *file_indices);
t_paths	*parse_arguments(int argc, char **argv, int *file_indices, int file_count);
void	free_paths(t_paths *paths);
t_file	*parse_path(char *path);

/* Execution functions */
void	list_directories(t_paths *paths, t_flags *flags);
void	list_directory(char *path, t_flags *flags,t_paths *paths, int is_recursive, int new_line );
void	sort_files(t_file **files, t_flags *flags);
void	get_subdirectories(t_paths *paths,t_file *files, t_flags *flags);

/*  helper */
t_file *ft_reverse(t_file *head);
int		get_terminal_width(void);

/* Display functions */
void    display_files(t_file *files, t_flags *flags);
void    display_long_format(t_file *files, t_flags *flags);
void    display_regular_format(t_file *files, t_flags *flags);
int     get_file_count_and_max_len(t_file *files, int *max_len);
int     get_terminal_width(void);
char    **collect_file_names(t_file *files, int file_count);
void	display_file_type_permission(t_file *file);
void	print_filenames(t_display *display, int file_count);
/* Calculation functions */
 
void    calculate_column_width(int *col_widths, char **file_names, int rows, int cols);
int     calculate_optimal_columns(int file_count, char **file_names, int term_width);
int     calculate_total_blocks(t_file *files);
void	calculate_padding(t_file *files, t_padding *pad);
int		calculate_total_width(int cols, int file_count, char **file_names);
size_t	calculate_number_length(size_t number);

#endif