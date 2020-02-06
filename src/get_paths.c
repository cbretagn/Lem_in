/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:41:09 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/06 17:22:34 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int	print_debug(t_path	*routes)
{
	int		i;

	i = -1;
	while (++i < routes->size)
	{
		if (routes->tab[i]->size < 2)
			break ;
		int j = -1;
		while (++j < routes->tab[i]->size)
			printf("%d ", routes->tab[i]->tab[j]);
		printf("\n");
	}
}

t_path		*get_paths(t_anthill *anthill, int **matrix)
{
	t_path		*routes;
	int			node;
	int			i;
	int			j;
	int			path;

	i = anthill->connectors[anthill->start]->size < anthill->connectors[anthill
		->end]->size ? anthill->connectors[anthill->start]->size : anthill->
		connectors[anthill->end]->size;
	if (!(routes = create_path_tab(i)))
		exit(-1);
	i = -1;
	path = 0;
	while (++i < anthill->nb_room)
	{
		routes->path_length[path] = 0;
		if (matrix[anthill->start][i] != -1 && matrix[i][anthill->start] == -1)
		{
			routes->tab[path] = push_int(routes->tab[path], anthill->start);
			routes->tab[path] = push_int(routes->tab[path], i);
			node = i;
			while (node != anthill->end)
			{
				j = -1;
				while (++j < anthill->nb_room)
				{
					if (matrix[node][j] != -1 && matrix[j][node] == -1)
					{
						routes->tab[path] = push_int(routes->tab[path], j);
						node = j;
						break ;
					}
				}
			}
		}
		path++;
	}
	print_debug(routes);
	return (routes);
}
