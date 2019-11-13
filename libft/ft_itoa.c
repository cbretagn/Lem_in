/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:02:32 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/18 18:34:54 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_size(int n)
{
	size_t		size;
	long		hold;

	size = 1;
	hold = n;
	if (hold < 0)
	{
		size++;
		hold = hold * -1;
	}
	while (hold > 0)
	{
		hold = hold / 10;
		size++;
	}
	if (n == 0)
		size++;
	return (size);
}

char			*ft_itoa(int n)
{
	char	*send;
	size_t	size;
	long	hold;

	size = ft_size(n);
	hold = n;
	if (!(send = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	send[size - 1] = '\0';
	size--;
	if (n < 0)
	{
		send[0] = '-';
		hold = hold * -1;
	}
	if (n == 0)
		send[0] = '0';
	while (hold > 0)
	{
		size--;
		send[size] = hold % 10 + '0';
		hold = hold / 10;
	}
	return (send);
}
