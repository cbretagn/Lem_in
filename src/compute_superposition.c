/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_superposition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:32:28 by cbretagn          #+#    #+#             */
/*   Updated: 2020/01/27 18:58:48 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		shortest_path_to(t_anthill *anthill, t_dijkstra *tab, int node)
{
	int		curr;

	curr = anthill->start;
	while (curr != node)
	{
		check_neighbours(anthill, tab, curr);
		tab[curr].visited = VISITED;
		curr = find_min(tab, anthill->nb_room);
	}
}


t_path			*superposition_path(t_anthill *anthill, int node)
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
		shortest_path_to(anthill, tab, node);
		routes = get_route(routes, tab, node, anthill->start);
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
	free(tab);
	tab = NULL;
	return (routes);
}

#include <stdio.h>

void		print_suggestions(t_anthill *anthill)
{
	int		fd;
	int		i;
	int		node;
	t_path	*routes;

	fd = open("test_superposition", O_CREAT | O_TRUNC | O_RDWR);
	i = -1;
	while (++i < anthill->connectors[anthill->end]->size)
	{
		node = anthill->connectors[anthill->end]->tab[i].name;
		routes = superposition_path(anthill, node);
		dprintf(fd, "option %d :\n", i);
		int j = -1;
		while (++j < routes->tab[i]->size)
		{
			dprintf(fd, "%d %s ", routes->tab[i]->tab[j], 
					anthill->rooms[routes->path_length[i]]);
		}
		dprintf(fd, "total length is \033[1;32m%d\033[0m\n\n", 
				routes->path_length[j]);
		free(routes);
		routes = NULL;
	}
}
