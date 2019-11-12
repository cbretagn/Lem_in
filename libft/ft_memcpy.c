/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:45:34 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/21 19:48:51 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*dstcp;
	char			*srccp;
	unsigned long	i;

	dstcp = (char *)dst;
	srccp = (char *)src;
	i = 0;
	while (i < n)
	{
		*(dstcp + i) = (char)*(srccp + i);
		i++;
	}
	return (dst);
}
