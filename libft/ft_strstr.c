/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 20:39:21 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/11 15:42:00 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		len;
	int		i;
	char	*send;

	len = ft_strlen(needle);
	send = (char*)haystack;
	if (*needle == '\0')
		return (send);
	while (*send)
	{
		i = 0;
		while (send[i] == needle[i] && needle[i] != '\0')
		{
			if (i == len - 1)
				return (send);
			i++;
		}
		send++;
	}
	return (NULL);
}
