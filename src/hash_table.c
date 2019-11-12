/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:11:49 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/12 15:50:17 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		delete_table(char **tab, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
}

int			hash_fun(char *str)
{
	char	c;
	int		i;
	int		hash;

	hash = 456;
	i = -1;
	while ((c = str[++i]))
		hash = hash * 31 + c;
	return (hash);
}

char		**put_in_table(char *str, char **tab, int size)
{
	int		hash;
	int		quadra;

	quadra = 1;
	hash = hash_fun(str) % size;
	while (tab[hash] != NULL)
	{
		if (ft_strcmp(str, tab[hash]) == 0)
		{
			delete_table(tab, size);
			return (NULL);
		}
		hash = (hash + quadra * quadra) % size;
		quadra++;
	}
	if (!(tab[hash] = ft_strdup(str)))
	{
		delete_table(tab, size);
		return (NULL);
	}
	return (tab);
}

int			search_in_table(char *str, char **tab, int size)
{
	int		hash;
	int		quadra;

	quadra = 1;
	hash = hash_fun(str) % size;
	while (ft_strcmp(str, tab[hash]) != 0)
	{
		hash = (hash + quadra * quadra) % size;
		quadra++;
	}
	return (hash);
}
