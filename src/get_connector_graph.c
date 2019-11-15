/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connector_graph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:21:34 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/15 19:24:09 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_anthill	*find_next_connector(int start, t_anthill *anthill, int hub_name)
{
	int		distance;
	int		next;
	int		prev;

	next = start;
	prev = hub_name;
	distance = 1;
	while (NODES[next]->size == 2)
	{
		prev = next;
		next = NODES[next]->tab[0] == prev ? NODES[next]->tab[1]
			: NODES[next]->tab[0];
		distance++;
	}
	if (NODES[next]->size < 2)
		return (anthill);
	if (!CONNECTORS[hub_name])
		CONNECTORS[hub_name] = create_connector(BASE_CONNECTORS);
	CONNECTORS[hub_name] = push_vertex(CONNECTORS[hub_name], next, distance);
	return (anthill);
}

t_anthill		*create_connector_graph(t_anthill *anthill)
{
	int			i;
	int			j;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!ROOMS[i])
			continue ;
		if (NODES[i]->size > 2)
		{
			j = -1;
			CONNECTORS[i] = create_connector(BASE_CONNECTORS);
			while (++j < NODES[i]->size)
				anthill = find_next_connector(NODES[i]->tab[j], anthill, i);
		}
			// it's a connector, create t_vertex at CONNECTORS[i] and fill it
			// w/ all the vertices it's connected to
	}
	return (anthill);
}
