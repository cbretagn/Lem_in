/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:19:32 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/19 11:38:16 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_sep(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	char		*send;
	const char	*end;
	int			i;

	if (!s)
		return (NULL);
	i = 0;
	while (*s && ft_sep(*s))
		s++;
	if (*s)
		end = s + ft_strlen(s) - 1;
	else
		end = s - 1;
	while (end > s && ft_sep(*end))
		end--;
	if (!(send = (char *)malloc(sizeof(char) * (end - s) + 2)))
		return (NULL);
	while (*s && s < end + 1)
	{
		*(send + i) = *s;
		i++;
		s++;
	}
	*(send + i) = '\0';
	return (send);
}
