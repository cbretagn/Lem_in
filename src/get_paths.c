/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:41:09 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/12 17:24:00 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

static void	check(t_path *routes, int nb, int end)
{
	int		i;
	int		j;
	int		check = 0;

	i = -1;
	while (++i < routes->size)
	{
		if (routes->path_length[i] == INT_MAX)
			continue ;
		j = 0;
		while (j < routes->tab[i]->size)
		{
			if (routes->tab[i]->tab[j] == nb && routes->tab[i]->tab[j] != end)
			{
				check++;
				if (check > 1)
					printf("Collision : room %d\n", nb);
			}
			j += 2;
		}
	}
}

static void	check_collision(t_path *routes, int end)
{
	int		i;
	int		j;

	i = -1;
	while (++i < routes->size)
	{
		if (routes->path_length[i] == INT_MAX)
			continue ;
		j = 0;
		while (j < routes->tab[i]->size)
		{
			check(routes, routes->tab[i]->tab[j], end);
			j += 2;
		}
	}
}

static void	print_debug(t_path	*routes, t_anthill *anthill)
{
	int		i;

	i = -1;
	printf("\n\nprinting path with struct\n\n");
	while (++i < routes->size)
	{
		int j = 0;
		while (j < routes->tab[i]->size)
		{
			printf("\033[1;32m%d \033[0mfrom %d ", routes->tab[i]->tab[j],
					routes->tab[i]->tab[j + 1]);
			j += 2;
		}
		if (routes->path_length[i] == INT_MAX)
			printf("\033[1;31mFULL SIZE %d \033[0m", routes->path_length[i]);
		else
			printf("\033[1;34mFULL SIZE %d \033[0m", routes->path_length[i]);
		printf("\033[0;31m ANTS %d\n\033[0m", routes->nb_ants[i]);
	}
	check_collision(routes, anthill->end);
}

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
				next = i;
				from = matrix[node][i];
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
	i = -1;
	path = 0;
	while (++i < anthill->nb_room)
	{
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
	print_debug(routes, anthill);
	printf("nb_lines w/ edmond karps %d\n", nb_lines(routes));
	return (routes);
}
