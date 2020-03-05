/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:11:49 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/05 16:54:25 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void				delete_table(char **tab, int size)
{
	int				i;

	i = -1;
	while (++i < size)
		ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
}

long int			hash_fun(char *str)
{
	char			c;
	int				i;
	long int		hash;

	hash = 456;
	i = -1;
	while ((c = str[++i]) && i < 10)
		hash = hash * 31 + c;
	return (hash);
}

char				**put_in_table(char *str, char **tab, int size)
{
	long int		hash;

	hash = (int)(hash_fun(str) % size);
	while (tab[hash] != NULL)
	{
		if (ft_strcmp(str, tab[hash]) == 0)
		{
			delete_table(tab, size);
			return (NULL);
		}
		hash = (hash + 1) % size;
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
	int		i;

	i = 0;
	hash = hash_fun(str) % size;
	while (ft_strcmp(str, tab[hash]) != 0 && i < size)
	{
		hash = (hash + 1) % size;
		i++;
	}
	if (i == size)
		exit(EXIT_FAILURE);
	return (hash);
}
