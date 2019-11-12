/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 18:04:50 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/19 11:35:44 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_ptr;
	const char	*src_ptr;
	int			len2;

	dst_ptr = (char *)dst;
	src_ptr = (const char *)src;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		len2 = (int)len;
		while (--len2 >= 0)
			*(dst_ptr + len2) = *(src_ptr + len2);
	}
	return (dst);
}
