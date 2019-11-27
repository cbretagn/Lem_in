/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/27 15:57:50 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#define SIZE 400

static void		print_tab(char **tab, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (tab[i])
			ft_putendl(tab[i]);
		else
			ft_putendl("(NULL)");
	}
}

#include <stdio.h>

static void		print_dynode(t_dynode **nodes, char **rooms, int size)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		printf("node %d / %s is connected to nodes : ", i, rooms[i]);
		j = -1;
		while (++j < nodes[i]->size)
			printf("%d ", nodes[i]->tab[j]);
		printf("\n");
	}
}

static void		print_smallergraph(t_anthill *anthill)
{
	int		i;
	int		j;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!CONNECTORS[i])
			continue ;
		printf("\nhub %d is connected to hubs : ", i);
		j = -1;
		while (++j < CONNECTORS[i]->size)
			printf("%d at distance %d from %d, ", CONNECTORS[i]->tab[j].name,
					CONNECTORS[i]->tab[j].dist, CONNECTORS[i]->tab[j].from);
	}
	printf("\n");
}

static void		print_solo_and_connectors(t_dynode **nodes, int size)
{
	int		solo;
	int		connectors;
	int		i;

	i = -1;
	solo = 0;
	connectors = 0;
	while (++i < size)
	{
		if (nodes[i]->size == 1)
			solo++;
		if (nodes[i]->size > 2)
			connectors++;
	}
	printf("There are %d solo nodes and %d connectors in this graph\n",
			solo, connectors);
}

int				main(int argc, char **argv)
{
	t_anthill	*anthill;
	char		*file;
	char		*graph;
	t_data		*data;
	t_path		*routes;
	int			i;
	int			j;

	i = -1;
	j = -1;
	if (!(data = init_struct()) || argc != 2)
		return (0);
	if (!(file = read_file(argv[1])))
		return (0);
	if (!(graph = ft_strsub(file, 0, check_file(file, data))))
		return (0);
	anthill = create_anthill(data->rooms);
	if (anthill)
		write(1, "Anthill is here !\n", 18);
	printf("data contains start %d end %d tubes %d rooms %d ants %d start %s end %s\n",
			data->start, data->end, data->tubes, data->rooms, data->ants,
			data->start_room, data->end_room);
	anthill = parser(graph, anthill, data); //size temporary // size needed ?
	anthill = create_connector_graph(anthill);
	if (anthill)
	{
		write(1, "\nAnthill is still here !\n", 25);
		print_tab(anthill->rooms, data->rooms);
		print_dynode(anthill->nodes, anthill->rooms, anthill->nb_room);
		i = -1;
		while (++i < anthill->nb_room)
		{
			if (!CONNECTORS[i])
				continue ;
			anthill = sort(anthill, i);
		}
		print_smallergraph(anthill);
		print_solo_and_connectors(anthill->nodes, anthill->nb_room);
		/*routes = next_shortest_path(anthill);
		while (++j < routes->size)
		{
			i = -1;
			printf("shortest path is %d : ", j);
			while (++i < routes->tab[j]->size)
			{
				printf("%d %s ", routes->tab[j]->tab[i], anthill->rooms
								[routes->tab[j]->tab[i]]);
			}
			printf("total length is \033[1;32m%d\033[0m\n", routes->path_length[j]);
		}*/
	}
	return (0);
}
