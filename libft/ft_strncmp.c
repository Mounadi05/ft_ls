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
