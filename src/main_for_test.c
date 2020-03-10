/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 18:19:54 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static char			*create_file(t_data *data, char *str)
{
	char			*file;
	int				x;
	char			*graph;

	if (!(file = read_file(str)))
		exit(-2);
	x = check_file(file, data);
	if (x == 0 || !(graph = ft_strsub(file, 0, x)))
		exit(-2);
	return (graph);
}

static t_anthill	*parse_anthill(char *graph, t_data *data, t_anthill *anthill)
{
	anthill = create_anthill(data->rooms);
	anthill = parser(graph, anthill, data);
	anthill = create_connector_graph(anthill);
	return (anthill);
}

int					main(int argc, char **argv)
{
	t_anthill		*anthill = NULL;
	char			*graph;
	t_data			*data;
	t_path			*routes = NULL;
	t_path			*routes1 = NULL;
	t_path			*routes2 = NULL;
	int				lines1 = 0;
	int				lines2 = 0;
	
	if (argc != 2 || !(data = init_struct()))
		return (0);
	if (!(graph = create_file(data, argv[1])))
		return (0);
	if (!(anthill = parse_anthill(graph, data, anthill)))
		return (0);
	routes = next_shortest_path(anthill);
	routes = get_direct_path(routes, anthill);
	routes = get_nb_ants(routes, anthill->ants);
	routes = get_real_routes(routes, anthill);
	debugger(routes, anthill, "log_file_routes");
	if (anthill)
	{
		routes1 = edmonds_karp1(anthill);
		routes1 = get_nb_ants(routes1, anthill->ants);
		lines1 = routes1->path_length[0] + routes1->nb_ants[0] - 1;
		debugger(routes1, anthill, "log_file_routes1");
		routes2 = edmonds_karp2(anthill);
		routes2 = get_nb_ants(routes2, anthill->ants);
		lines2 = routes2->path_length[0] + routes2->nb_ants[0] - 1;
		debugger(routes2, anthill, "log_file_routes2");
	}
	int lines;
	lines = nb_lines(routes);
	ft_putendl(graph);
	if (lines <= lines1 && lines <= lines2)
	{
		print_ants(anthill, routes);
	}
	else if (lines1 <= lines && lines1 <= lines2)
	{
		print_ants(anthill, routes1);
	}
	else
	{
		print_ants(anthill, routes2);
	}
	free_data(data);
	ft_strdel(&graph);
	return (0);
}
