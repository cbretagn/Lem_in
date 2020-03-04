/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_EK_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:16:14 by sadahan           #+#    #+#             */
/*   Updated: 2020/02/25 19:16:20 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

int	**init_mat_capacity(t_anthill *a)
{
	int		**m;
	int		i;
	int		j;

	i = -1;
	if (!(m = (int **)malloc(sizeof(int *) * a->nb_room * 2)))
		exit (-2);
	while (++i < a->nb_room * 2)
	{
		if (!(m[i] = (int *)malloc(sizeof(int) * a->nb_room * 2)))
			exit(-2);
		j = -1;
		while (++j < a->nb_room * 2)
			m[i][j] = 0;
		j = -1;
		while (++j < a->nodes2[i]->size)
			m[i][a->nodes2[i]->tab[j]] = 1;
	}
	m[a->start][a->start + a->nb_room] = INT_MAX;
	m[a->start + a->nb_room][a->start] = INT_MAX;
	m[a->end][a->end + a->nb_room] = INT_MAX;
	m[a->end + a->nb_room][a->end] = INT_MAX;
	return (m);
}

int	**init_matrice(int size, int nb)
{
	int		**m;
	int		i;
	int		j;

	i = -1;
	if (!(m = (int **)malloc(sizeof(int *) * size)))
		exit (-2);
	while (++i < size)
	{
		if (!(m[i] = (int *)malloc(sizeof(int) * size)))
			exit(-2);
		j = -1;
		while (++j < size)
			m[i][j] = nb;
	}
	return (m);
}

int		*init_parent(int size)
{
	int *parent;
	int	i;

	i = -1;
	if (!(parent = (int *)malloc(sizeof(int) * size)))
		exit(-2);
	while (++i < size)
		parent[i] = -1;
	return (parent);
}
