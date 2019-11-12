/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 20:56:00 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/11 16:06:48 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int				len_needle;
	int				i;
	unsigned long	j;
	char			*send;

	send = (char *)haystack;
	if (*needle == '\0')
		return (send);
	len_needle = ft_strlen(needle);
	j = -1;
	while (++j < len && *send)
	{
		i = 0;
		while (send[i] == needle[i])
		{
			if (j + i >= len)
				break ;
			if (i == len_needle - 1)
				return (send);
			i++;
		}
		send++;
	}
	return (NULL);
}
