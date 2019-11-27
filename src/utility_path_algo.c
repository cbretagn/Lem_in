/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_path_algo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:34:39 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/27 15:15:36 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"


t_path			*create_path_tab(int size)
{
	t_path		*ret;
	int			i;

	i = -1;
	if (!(ret = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	if (!(ret->tab = (t_dynode **)malloc(sizeof(t_dynode *) * size)))
		return (NULL);
	if (!(ret->path_length = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	while (++i < size)
	{
		if (!(ret->tab[i] = create_dynode(BASE_DYN_NODES)))
			return (NULL);
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

//init tab w/ NAN NOTVIS and start at 0
//quicksort

static t_anthill		*switch_vertex(t_anthill *anthill, int co, int a, int b)
{
	int		tmp_dist;
	int		tmp_from;
	int		tmp_name;

	tmp_dist = CONNECTORS[co]->tab[a].dist;
	tmp_from = CONNECTORS[co]->tab[a].from;
	tmp_name = CONNECTORS[co]->tab[a].name;
	CONNECTORS[co]->tab[a].dist = CONNECTORS[co]->tab[b].dist;
	CONNECTORS[co]->tab[a].from = CONNECTORS[co]->tab[b].from;
	CONNECTORS[co]->tab[a].name = CONNECTORS[co]->tab[b].name;
	CONNECTORS[co]->tab[b].dist = tmp_dist;
	CONNECTORS[co]->tab[b].from = tmp_from;
	CONNECTORS[co]->tab[b].name = tmp_name;
	return (anthill);
}

t_anthill				*sort(t_anthill *anthill, int co)
{
	int			i;
	int			j;

	i = 0;
	while (++i < CONNECTORS[co]->size)
	{
		j = i - 1;
		while (CONNECTORS[co]->tab[i].dist < CONNECTORS[co]->tab[j].dist
					&& j >= 0)
		{
			switch_vertex(anthill, co, i, j);
			i--;
			j--;
		}
	}
	return (anthill);
}
