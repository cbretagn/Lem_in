/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connector_graph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:21:34 by cbretagn          #+#    #+#             */
/*   Updated: 2020/01/16 13:48:52 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_anthill	*find_next_connector(int start,
						t_anthill *anthill, int hub)
{
	int				distance;
	int				next;
	int				prev;
	int				tmp;
	int				from;

	next = start;
	from = start;
	prev = hub;
	distance = 1;
	while (NODES[next]->size == 2 && next != anthill->end
		&& next != anthill->start)
	{
		tmp = next;
		next = NODES[next]->tab[0] == prev ? NODES[next]->tab[1]
			: NODES[next]->tab[0];
		prev = tmp;
		distance++;
	}
	if (NODES[next]->size < 2 && next != anthill->end && next != anthill->start)
		return (anthill);
	CONNECTORS[hub] = push_vertex(CONNECTORS[hub], next, distance, from);
	return (anthill);
}

t_anthill			*create_connector_graph(t_anthill *anthill)
{
	int				i;
	int				j;

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
