/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_EK_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:16:14 by sadahan           #+#    #+#             */
/*   Updated: 2020/02/06 17:39:36 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int	**init_matrice(t_anthill *a)
{
	int		**m;
	int		i;
	int		j;

	i = -1;
	if (!(m = (int **)malloc(sizeof(int *) * a->nb_room)))
		exit (-2);
	while (++i < a->nb_room)
	{
		if (!(m[i] = (int *)malloc(sizeof(int) * a->nb_room)))
			exit(-2);
		j = -1;
		while (++j < a->nb_room)
			m[i][j] = 1;
	}
	return (m);
}

int		*init_parent(t_anthill *a)
{
	int *parent;
	int	i;

	i = -1;
	if (!(parent = (int *)malloc(sizeof(int) * a->nb_room)))
		exit(-2);
	while (++i < a->nb_room)
		parent[i] = -1;
	parent[a->start] = -2;
	return (parent);
}