/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:07:34 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/27 15:27:14 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
			if (tab[next].prev == -1 || tab[next].dist > 
					distance + tab[curr].dist)
			{
				tab[next].prev = curr;
				tab[next].dist = distance + tab[curr].dist;
			}
		}
	}
}

//if start check neighbours then mark start as visited
//then for each neighbour of start check them then mark them all as visited
//then for each of their neighbours repeat step 2
//
void			rec_dijkstra(t_anthill *anthill, t_dijkstra *tab, int curr)
{
	int		i;

	i = -1;
	if (curr == anthill->end)
		return ;
	check_neighbours(anthill, tab, curr);
	tab[curr].visited = VISITED;
	while (++i < CONNECTORS[curr]->size)
	{
		if (tab[CONNECTORS[curr]->tab[i].name].visited == NOTVIS)
			rec_dijkstra(anthill, tab, CONNECTORS[curr]->tab[i].name);
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
		tab[i].prev = -1;
	}
	tab[anthill->start].prev = anthill->start;
	tab[anthill->start].dist = 0;
	i = CONNECTORS[anthill->start]->size < CONNECTORS[anthill->end]->size ?
		CONNECTORS[anthill->start]->size : CONNECTORS[anthill->end]->size;
	if (!(routes = create_path_tab(i)))
		return (NULL);
	while (--i > 0)
	{
		rec_dijkstra(anthill, tab, anthill->start);
		routes = get_route(routes, tab, anthill->end, anthill->start);
		int	j = -1;
		while (++j < anthill->nb_room)
		{
			if (tab[j].visited != NAN)
			{
				tab[j].visited = NOTVIS;
				tab[j].prev = -1;
			}
		}
	}
	return (routes);
}
