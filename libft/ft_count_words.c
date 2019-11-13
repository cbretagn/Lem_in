/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 20:19:37 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/21 18:10:03 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char const *s, char c)
{
	int	send;

	if (!s)
		return (0);
	send = 0;
	while (*s)
	{
		if (*s != c)
			send++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (send);
}
