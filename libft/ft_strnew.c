/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:07:36 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/18 18:30:53 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*send;
	size_t	i;

	i = 0;
	if (!(send = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (i < size + 1)
	{
		send[i] = '\0';
		i++;
	}
	return (send);
}
