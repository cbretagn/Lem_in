/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <cbretagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:16:26 by cbretagn          #+#    #+#             */
/*   Updated: 2020/04/28 09:53:23 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_dijkstra		*init_dijkstra_tab(t_dijkstra *tab, t_anthill *anthill)
{
	int		i;

	i = -1;
	while (++i < anthill->nb_room)
	{
		tab[i].prev = -1;
		if (!(anthill->connectors[i]))
			tab[i].visited = NAN;
		else
			tab[i].visited = NOTVIS;
		tab[i].dist = 10000;
	}
	tab[anthill->start].prev = anthill->start;
	tab[anthill->start].dist = 0;
	return (tab);
}

t_dijkstra		*refresh_tab(t_dijkstra *tab, t_anthill *anthill)
{
	int		i;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (tab[i].visited != NAN)
		{
			tab[i].visited = NOTVIS;
			tab[i].dist = 10000;
		}
	}
	tab[anthill->start].prev = anthill->start;
	tab[anthill->start].dist = 0;
	return (tab);
}
