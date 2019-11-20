/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connector_graph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:21:34 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/20 15:42:07 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_anthill	*find_next_connector(int start, t_anthill *anthill, int hub_name)
{
	int		distance;
	int		next;
	int		prev;
	int		tmp;

	next = start;
	prev = hub_name;
	distance = 1;
	ft_putnbr(NODES[next]->size);
	while (NODES[next]->size == 2)
	{
		tmp = next;
		next = NODES[next]->tab[0] == prev ? NODES[next]->tab[1]
			: NODES[next]->tab[0];
		prev = tmp;
		distance++;
	}
	if (NODES[next]->size < 2)
	{
		return (anthill);
	}
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
			if (!ROOMS[i])
				ft_putstr("(null)\n");
			else
				ft_putendl(ROOMS[i]);
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
