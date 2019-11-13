/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:53:04 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/17 17:46:26 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "libft.h"

size_t		ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	s_dest;
	size_t	s_src;
	size_t	i;

	i = 0;
	s_dest = ft_strlen(s1);
	s_src = ft_strlen(s2);
	if (n <= s_dest)
		return (n + s_src);
	s1 = s1 + s_dest;
	i = n - s_dest;
	while (--i > 0 && *s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
	return (s_dest + s_src);
}
