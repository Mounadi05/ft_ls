/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <mounadi1337@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:03:39 by amounadi          #+#    #+#             */
/*   Updated: 2021/11/08 18:03:36 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	else
		while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i]
			&& i < (n - 1))
			i++;
	return ((unsigned char )s1[i] - (unsigned char)s2[i]);
}

int ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
 		i++;
 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_strcasecmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && (ft_tolower((unsigned char)s1[i]) == ft_tolower((unsigned char)s2[i])))
		i++;
	return ((unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[i]));
}
