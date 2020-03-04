/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_path_algo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:34:39 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/25 14:47:12 by cbretagn         ###   ########.fr       */
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
		return (NULL);
	if (!(ret->tab = (t_dynode **)malloc(sizeof(t_dynode *) * size)))
		return (NULL);
	if (!(ret->path_length = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	if (!(ret->nb_ants = (int *)malloc(sizeof(int) * size)))
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

int			find_min(t_dijkstra *tab, int size)
{
 	int		ret;
 	int		dist;
 	int		i;

 	i = -1;
 	dist = INT_MAX;
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
