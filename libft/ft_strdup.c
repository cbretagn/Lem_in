/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:16:10 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/10 22:09:36 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*send;
	unsigned long	i;

	i = -1;
	if (!(send = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	while (++i < ft_strlen(s))
		send[i] = s[i];
	send[i] = '\0';
	return (send);
}
