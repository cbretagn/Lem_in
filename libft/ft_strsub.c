/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:01:28 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/18 17:37:07 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*send;
	char	*ptr_s;
	int		i;

	if (!s)
		return (NULL);
	ptr_s = (char *)(s + start);
	if (!(send = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = -1;
	while (++i < (int)len)
		*(send + i) = *(ptr_s + i);
	*(send + i) = '\0';
	return (send);
}
