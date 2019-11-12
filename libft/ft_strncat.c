/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:53:04 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/17 17:27:28 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned long len;
	unsigned long i;

	len = ft_strlen(s1);
	i = 0;
	while (*(s2 + i) != '\0' && i < n)
	{
		*(s1 + len + i) = *(s2 + i);
		i++;
	}
	*(s1 + len + i) = '\0';
	return (s1);
}
