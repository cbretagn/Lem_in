/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 15:47:53 by sadahan          ###   ########.fr       */
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

static t_anthill	*parse_anthill(char *graph, t_data *data,
						t_anthill *anthill)
{
	if (!(anthill = create_anthill(data->rooms)))
		return (NULL);
	if (!(anthill = parser(graph, anthill, data)))
		return (NULL);
	if (!(anthill = create_connector_graph(anthill)))
		return (NULL);
	return (anthill);
}

int					main(int argc, char **argv)
{
	t_anthill		*anthill;
	char			*graph;
	t_data			*data;
	t_path			*routes;
	int				verbose;

	anthill = NULL;
	routes = NULL;
	verbose = check_verbose(argc, argv);
	if (!(data = init_struct()))
		return (0);
	if (!(graph = create_file(data, argv[1 + verbose])))
		return (0);
	if (!(anthill = parse_anthill(graph, data, anthill)))
		return (0);
	routes = find_best_routes(anthill, routes);
	ft_putendl(graph);
	print_ants(anthill, routes);
	delete_anthill(anthill);
	free_path(routes);
	free_data(data);
	ft_strdel(&graph);
	return (0);
}