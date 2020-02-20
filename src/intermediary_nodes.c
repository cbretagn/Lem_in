/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intermediary_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:43:34 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/20 16:19:20 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_anthill	*create_intermediary(t_anthill *anthill, int node)
{
	t_connector		*temp;
	int				new;

	new = anthill->nb_room + node;
	if (!(anthill->connectors[new] = create_connector(BASE_CONNECTORS)))
		exit(-1);
	anthill->connectors[new] = push_vertex(anthill->connectors[new], new, 1, new);
	temp = anthill->connectors[node];
	anthill->connectors[node] = anthill->connectors[new];
	anthill->connectors[new] = temp;
	return (anthill);
}

t_anthill			*add_intermediary_nodes(t_anthill *anthill)
{
	int		i;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (i == anthill->start || i == anthill->end || !anthill->connectors[i])
			continue ;
		anthill = create_intermediary(anthill, i);
	}
	return (anthill);
}
