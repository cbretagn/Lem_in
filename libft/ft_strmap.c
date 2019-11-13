/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:04:34 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/18 17:26:56 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		len;
	char	*send;
	char	*ptr_s;

	if (s)
	{
		len = ft_strlen(s);
		ptr_s = (char *)s;
		if (!(send = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		send[len] = '\0';
		while (--len >= 0)
			send[len] = f(*(ptr_s + len));
		return (send);
	}
	return (NULL);
}
