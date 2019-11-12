/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:26:43 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/13 15:42:57 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ptr_s;

	ptr_s = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*ptr_s == (unsigned char)c)
			return (ptr_s);
		ptr_s++;
	}
	return (NULL);
}
