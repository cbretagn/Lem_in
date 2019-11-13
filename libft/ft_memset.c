/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 16:19:43 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/11 16:33:16 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long i;
	unsigned char *temp;

	i = -1;
	temp = (unsigned char *)b;
	while (++i < len)
		*(temp + i) = (unsigned char)c;
	return (b);
}
