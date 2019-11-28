/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connector_graph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:21:34 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/28 14:30:54 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_anthill	*find_next_connector(int start,
						t_anthill *anthill, int hub_name)
{
	int		distance;
	int		next;
	int		prev;
	int		tmp;
	int		from;

	next = start;
	from = start;
	prev = hub_name;
	distance = 1;
	while (NODES[next]->size == 2 && next != anthill->end && next != anthill->start)
	{
		tmp = next;
		next = NODES[next]->tab[0] == prev ? NODES[next]->tab[1]
			: NODES[next]->tab[0];
		prev = tmp;
		distance++;
	}
	if (NODES[next]->size < 2 && next != anthill->end && next != anthill->start)
		return (anthill);
	CONNECTORS[hub_name] = push_vertex(CONNECTORS[hub_name], next, distance, from);
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
		if (NODES[i]->size > 2 || i == anthill->start || i == anthill->end)
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
