/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:22:51 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/10 22:09:57 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*send;

	send = (char *)s;
	while (*send)
	{
		if (*send == c)
			return (send);
		send++;
	}
	if (c == '\0')
		return (send);
	return (NULL);
}
