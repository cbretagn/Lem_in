/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:29:04 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/11 15:33:44 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*send;
	unsigned long	i;

	i = ft_strlen(s);
	send = (char *)s;
	send = send + i;
	while (i > 0)
	{
		if (*send == c)
			return (send);
		send--;
		i--;
	}
	if (*send == c)
		return (send);
	else
		return (NULL);
}
