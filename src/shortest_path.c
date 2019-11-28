/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:07:34 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/28 17:56:29 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

//create tab of paths
//push next node on path
//
//create tab of dijstra
//fill w/ NULL for non connectors
//connectors start w/prev at -1 and dist at -1
//
//parcourir le graphe, remplir djikstra
//remplir chemin
//for each node in path --> (NULL) except start + end
//
//repeat till s_path filled or no path;
//

void			check_neighbours(t_anthill *anthill, t_dijkstra *tab, int curr)
{
	int		i;
	int		next;
	int		distance;

	i = -1;
	while (++i < CONNECTORS[curr]->size)
	{
		next = CONNECTORS[curr]->tab[i].name;
		distance  = CONNECTORS[curr]->tab[i].dist;
		if (tab[next].visited == VISITED || tab[next].visited == NAN)
			continue ;
		else
		{
			if (tab[next].dist > distance + tab[curr].dist)
			{
				tab[next].prev = curr;
				tab[next].dist = distance + tab[curr].dist;
			}
		}
	}
}

//while i != end check neighbours, mark as visited choose next one (closest)
//repeat

void			rec_dijkstra(t_anthill *anthill, t_dijkstra *tab)
{
	int		curr;

	curr = anthill->start;
	while (curr != anthill->end)
	{
		check_neighbours(anthill, tab, curr);
		tab[curr].visited = VISITED;
		curr = find_min(tab, anthill->nb_room);
	}
}

t_path			*get_route(t_path *routes, t_dijkstra *tab, int end, int start)
{
	int		i;
	int		length;

	if (tab[end].prev < 0)
		return (routes);
	i = routes->size;
	routes->path_length[i] = tab[end].dist;
	while (end != start)
	{
		routes->tab[i] = push_int(routes->tab[i], end);
		end = tab[end].prev;
		if (end != start)
		{
			tab[end].visited = NAN;
		}
	}
	routes->tab[i] = push_int(routes->tab[i], end);
	routes->size++;
	return (routes);
}

static int		compute_stop(t_path *routes, int ants)
{
	int		j;
	int		ret;
	int		curr;
	int		sub;

	if (routes->size <= 1 || ants == 1)
		return (ants);
	ret = ants;
	j = routes->size - 1;
	curr = routes->size - 1;
	while (--j >= 0)
	{
		sub = (routes->path_length[curr] - routes->path_length[j]);
		ret -= sub;
	}
	printf("ants = %d last sub %d\n", ret, sub);
	return (ret);
}

t_path			*next_shortest_path(t_anthill *anthill)
{
	t_dijkstra		*tab;
	int				i;
	t_path			*routes;

	i = -1;
	if (!(tab = (t_dijkstra *)malloc(sizeof(t_dijkstra) * anthill->nb_room)))
		return (NULL);
	while (++i < anthill->nb_room)
	{
		if (!CONNECTORS[i])
			tab[i].visited = NAN;
		else
			tab[i].visited = NOTVIS;
		tab[i].dist = 10000;
	}
	tab[anthill->start].prev = anthill->start;
	tab[anthill->start].dist = 0;
	i = CONNECTORS[anthill->start]->size < CONNECTORS[anthill->end]->size ?
		CONNECTORS[anthill->start]->size : CONNECTORS[anthill->end]->size;
	i = anthill->ants == 1 ? 1 : i;
	if (!(routes = create_path_tab(i)))
		return (NULL);
	while (--i >= 0)
	{
		rec_dijkstra(anthill, tab);
		routes = get_route(routes, tab, anthill->end, anthill->start);
		if ((compute_stop(routes, anthill->ants) <= 0))
				break ;
		int	j = -1;
		while (++j < anthill->nb_room)
		{
			if (tab[j].visited != NAN)
			{
				tab[j].visited = NOTVIS;
				tab[j].dist = 10000;
			}
		}
		tab[anthill->start].prev = anthill->start;
		tab[anthill->start].dist = 0;
	}
	printf("final i %d\n", i);
	return (routes);
}
