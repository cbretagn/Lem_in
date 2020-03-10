/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_connector_graph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:21:34 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 18:02:04 by sadahan          ###   ########.fr       */
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
	while (anthill->nodes[next]->size == 2 && next != anthill->end
		&& next != anthill->start)
	{
		tmp = next;
		next = anthill->nodes[next]->tab[0] == prev ?
			anthill->nodes[next]->tab[1] : anthill->nodes[next]->tab[0];
		prev = tmp;
		distance++;
	}
	if (anthill->nodes[next]->size < 2 && next != anthill->end
		&& next != anthill->start)
		return (anthill);
	anthill->connectors[hub] = push_vertex(anthill->connectors[hub],
		next, distance, from);
	return (anthill);
}

t_anthill			*create_connector_graph(t_anthill *anthill)
{
	int				i;
	int				j;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!anthill->rooms[i])
			continue ;
		if (anthill->nodes[i]->size > 2 || i == anthill->start
			|| i == anthill->end)
		{
			j = -1;
			anthill->connectors[i] = create_connector(BASE_CONNECTORS);
			while (++j < anthill->nodes[i]->size)
				anthill = find_next_connector(anthill->nodes[i]->tab[j],
					anthill, i);
		}
	}
	return (anthill);
}
