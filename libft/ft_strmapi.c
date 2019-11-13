/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:37:13 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/18 17:29:52 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*send;
	char			*ptr_s;
	int				i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = -1;
	ptr_s = (char *)s;
	if (!(send = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (++i < (int)len)
	{
		*(send + i) = f(i, *ptr_s);
		ptr_s++;
	}
	*(send + i) = '\0';
	return (send);
}
