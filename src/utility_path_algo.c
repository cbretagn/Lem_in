/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_path_algo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:34:39 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 18:36:46 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

t_path			*create_path_tab(int size)
{
	t_path		*ret;
	int			i;

	i = -1;
	if (!(ret = (t_path *)malloc(sizeof(t_path))))
		exit_malloc(-2);
	if (!(ret->tab = (t_dynode **)malloc(sizeof(t_dynode *) * size)))
		exit_malloc(-2);
	if (!(ret->path_length = (int *)malloc(sizeof(int) * size)))
		exit_malloc(-2);
	if (!(ret->nb_ants = (int *)malloc(sizeof(int) * size)))
		exit_malloc(-2);
	while (++i < size)
	{
		if (!(ret->tab[i] = create_dynode(BASE_DYN_NODES)))
			exit_malloc(-2);
	}
	ret->size = 0;
	ret->cap = size;
	return (ret);
}

void			delete_path_tab(t_path *del)
{
	int		i;

	i = -1;
	while (++i < del->size)
	{
		free(del->tab[i]);
		del->tab[i] = NULL;
	}
	free(del->path_length);
	del->path_length = NULL;
	free(del->tab);
	del->tab = NULL;
	free(del);
	del = NULL;
}

int				find_min(t_dijkstra *tab, int size)
{
	int		ret;
	int		dist;
	int		i;

	i = -1;
	dist = INT_MAX;
	ret = -1;
	while (++i < size)
	{
		if (tab[i].visited != NOTVIS)
			continue ;
		if (tab[i].dist < dist)
		{
			ret = i;
			dist = tab[i].dist;
		}
	}
	return (ret);
}
