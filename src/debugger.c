/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:37:05 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/05 18:09:05 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <stdio.h>

static int		check_connected_nodes(t_anthill *anthill, int node, int next)
{
	int		i;

	i = -1;
	while (++i < anthill->nodes[node]->size)
	{
		if (anthill->nodes[node]->tab[i] == next)
			return (0);
	}
	return (-1);
}

static void		check_validity(int fd, t_path *routes, t_anthill *anthill)
{
	int		i;
	int		j;
	int		error;

	i = -1;
	while (++i < routes->size)
	{
		error = 0;
		dprintf(fd, "On path %d :\n", i);
		if (routes->tab[i]->tab[0] != anthill->start)
		{
			dprintf(fd, "Path does not start at start room\n");
			error++;
		}
		if (routes->tab[i]->tab[routes->tab[i]->size - 1] != anthill->end)
		{
			dprintf(fd, "Path does not end at end room\n");
		}
		j = -1;
		while (++j < routes->tab[i]->size - 1)
		{
			if (check_connected_nodes(anthill, routes->tab[i]->tab[j],
						routes->tab[i]->tab[j + 1]) < 0)
			{
				dprintf(fd, "Node %d %s and node %d %s are not connected\n",
						routes->tab[i]->tab[j], anthill->rooms[routes->tab[i]->tab[j]],
						routes->tab[i]->tab[j + 1], anthill->rooms[routes->tab[i]->tab[j + 1]]);
				error++;
			}
		}
		if (error == 0)
			dprintf(fd, "No errors\n");
	}
}

void			debugger(t_path *routes, t_anthill *anthill, char *name)
{
	int		fd;

	fd = open(name, O_CREAT | O_TRUNC | O_RDWR);
	//dprintf(fd, "Checking collision\n\n");
	//check_collision(fd, routes, anthill);
	dprintf(fd, "\n\nChecking validity of routes\n\n");
	check_validity(fd, routes, anthill);
	close(fd);
}
