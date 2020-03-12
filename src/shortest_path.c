/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:07:34 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 16:51:00 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

void			check_neighbours(t_anthill *anthill, t_dijkstra *tab, int curr)
{
	int		i;
	int		next;
	int		distance;

	i = -1;
	while (++i < anthill->connectors[curr]->size)
	{
		next = anthill->connectors[curr]->tab[i].name;
		distance = anthill->connectors[curr]->tab[i].dist;
		if (tab[next].visited == VISITED || tab[next].visited == NAN
				|| (curr == anthill->start
					&& anthill->connectors[curr]->tab[i].name == anthill->end))
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

t_path			*get_route(t_path *routes, t_dijkstra *tab,
						int end, t_anthill *anthill)
{
	int		i;

	if (tab[end].prev < 0)
		return (routes);
	i = routes->size;
	routes->path_length[i] = tab[end].dist;
	while (end != anthill->start)
	{
		routes->tab[i] = push_int(routes->tab[i], end);
		end = tab[end].prev;
		if (end != anthill->start)
		{
			tab[end].visited = NAN;
		}
	}
	routes->tab[i] = push_int(routes->tab[i], end);
	routes->size++;
	return (routes);
}

int				compute_stop(t_path *routes, int ants)
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
	return (ret);
}

t_path			*next_shortest_path(t_anthill *ant)
{
	t_dijkstra		*tab;
	int				i;
	t_path			*routes;

	if (!(tab = (t_dijkstra *)malloc(sizeof(t_dijkstra) * ant->nb_room * 2)))
		return (NULL);
	tab = init_dijkstra_tab(tab, ant);
	if (!(routes = create_path_tab(ant->connectors[ant->start]->size * 2)))
		exit_malloc(-2);
	i = (ant->connectors[ant->start]->size < ant->connectors[ant->end]->size) ?
		ant->connectors[ant->start]->size : ant->connectors[ant->end]->size;
	i = ant->ants == 1 ? 1 : i;
	while (--i >= 0)
	{
		rec_dijkstra(ant, tab);
		routes = get_route(routes, tab, ant->end, ant);
		if ((compute_stop(routes, ant->ants) <= 0))
			break ;
		tab = refresh_tab(tab, ant);
	}
	free(tab);
	tab = NULL;
	return (routes);
}
