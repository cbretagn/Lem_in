/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/27 17:58:02 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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

static char		*create_file(t_data *data, char *str)
{
	char		*file;
	int			x;
	char		*graph;

	if (!(file = read_file(str)))
		exit(-2);
	x = check_file(file, data);
	// printf("x = %d\n", x);
	if (x == 0 || !(graph = ft_strsub(file, 0, x)))
		exit(-2);
	return (graph);
}

int				main(int argc, char **argv)
{
	t_anthill	*anthill;
	char		*graph;
	t_data		*data;
	t_path		*routes;
	int			i;
	int			j;
	
	i = -1;
	j = -1;
	if (argc != 2 || !(data = init_struct()))
		return (0);
	if (!(graph = create_file(data, argv[1])))
		return (0);
	anthill = create_anthill(data->rooms);
	anthill = parser(graph, anthill, data);
	anthill = create_connector_graph(anthill);
	ft_strdel(&graph);
	routes = next_shortest_path(anthill);
	routes = get_direct_path(routes, anthill);
	routes = get_nb_ants(routes, anthill->ants);
	routes = get_real_routes(routes, anthill);
	int lines;
	lines = nb_lines(routes);
	print_ants(anthill, routes);
	free_data(data);
	printf("%d", lines);
	return (0);
}
