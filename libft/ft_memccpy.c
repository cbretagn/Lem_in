/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 17:05:00 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/18 17:27:19 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dstcp;
	unsigned char	*srccp;
	int				i;

	dstcp = (unsigned char *)dst;
	srccp = (unsigned char *)src;
	i = -1;
	while (++i < (int)n)
	{
		*dstcp = *srccp;
		dstcp++;
		srccp++;
		if (*(srccp - 1) == (unsigned char)c)
			return (dstcp);
	}
	return (NULL);
}
