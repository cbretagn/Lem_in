/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:41:09 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 12:49:45 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

int			get_dist(int node, int to, int from, t_anthill *anthill)
{
	int		i;

	i = -1;
	while (++i < anthill->connectors[node]->size)
	{
		if (anthill->connectors[node]->tab[i].name == to
				&& anthill->connectors[node]->tab[i].from == from)
			return (anthill->connectors[node]->tab[i].dist);
	}
	return (INT_MAX);
}

t_dynode	*fetch_routes(t_dynode *path, t_anthill *anthill, int **matrix,
					int *distance)
{
	int		node;
	int		i;
	int		dist;
	int		next;
	int		from;

	node = path->tab[0];
	while (node != anthill->end)
	{
		i = -1;
		dist = INT_MAX;
		while (++i < anthill->nb_room)
		{
			if (matrix[node][i] != -1 && matrix[i][node] == -1
					&& get_dist(node, i, matrix[node][i], anthill) < dist)
			{
				from = matrix[node][i];
				next = i;
				dist = get_dist(node, i, matrix[node][i], anthill);
			}
		}
		path = push_int(path, next);
		path = push_int(path, from);
		*distance += dist;
		node = next;
	}
	return (path);
}

t_path		*get_paths(t_anthill *anthill, int **matrix)
{
	t_path		*routes;
	int			*distance;
	int			i;
	int			path;

	i = anthill->connectors[anthill->start]->size;
	if (!(distance = (int *)malloc(sizeof(int))))
		exit(-1);
	if (!(routes = create_path_tab(i)))
		exit(-1);
	routes = get_direct_path(routes, anthill);
	i = -1;
	path = routes->size;
	while (++i < anthill->nb_room)
	{
		if (i == anthill->end)
			continue ;
		if (matrix[anthill->start][i] != -1 && matrix[i][anthill->start] == -1)
		{
			routes->path_length[path] = get_dist(anthill->start, i,
					matrix[anthill->start][i], anthill);
			routes->tab[path] = push_int(routes->tab[path], i);
			routes->tab[path] = push_int(routes->tab[path], matrix[anthill->start][i]);
			path++;
			routes->size++;
		}
	}
	i = -1;
	while (++i < routes->size)
	{
		*distance = routes->path_length[i];
		routes->tab[i] = fetch_routes(routes->tab[i], anthill, matrix, distance);
		routes->path_length[i] = *distance;
	}
	routes = handle_collision(routes, anthill);
	routes = sort_routes(routes);
	routes = get_nb_ants(routes, anthill->ants);
	return (routes);
}
