/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:50:37 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/22 21:51:31 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_len_word(char const *s, char c)
{
	int i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static char		**ft_malloc_tab(char const *s, char c)
{
	char	**send;
	int		i;
	int		j;
	int		words;

	i = 0;
	words = ft_count_words(s, c);
	if (!(send = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (*s && i < words)
	{
		while (*s && *s == c)
			s++;
		j = ft_len_word(s, c);
		if (!(send[i] = (char *)malloc(sizeof(char) * (j + 1))))
		{
			while (--i >= 0)
				free(send[i]);
			free(send);
			return (NULL);
		}
		s = s + j;
		i++;
	}
	return (send);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**send;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	if (!(send = ft_malloc_tab(s, c)))
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			j = ft_len_word(s, c);
			ft_memcpy(send[i], s, j);
			send[i][j] = '\0';
			s = s + j;
			i++;
		}
	}
	send[i] = NULL;
	return (send);
}
