/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <cbretagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2020/04/27 23:04:47 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static char			*create_file(t_data *data)
{
	t_dstring		*file;
	int				x;
	char			*graph;

	if (!(file = read_file()))
	{
		write(2, "ERROR\n", 7);
		free_data(data);
		exit(-2);
	}
	x = check_file(file->str, data);
	if (x == 0 || !(graph = ft_strsub(file->str, 0, x)))
	{
		write(2, "ERROR\n", 7);
		delete_dstring(file);
		free_data(data);
		exit(-2);
	}
	delete_dstring(file);
	return (graph);
}

static t_anthill	*parse_anthill(char *graph, t_data *data,
						t_anthill *anthill)
{
	if (!(anthill = create_anthill(data->rooms)))
	{
		write(2, "ERROR\n", 6);
		return (NULL);
	}
	if (!(anthill = parser(graph, anthill, data)))
	{
		write(2, "ERROR\n", 6);
		ft_strdel(&graph);
		free_data(data);
		return (NULL);
	}
	if (!(anthill = create_connector_graph(anthill)))
	{
		write(2, "ERROR\n", 6);
		return (NULL);
	}
	return (anthill);
}

static void			print_clean(char *graph, t_anthill *anthill,
					t_path *routes, t_data *data)
{
	if (routes)
	{
		ft_putendl(graph);
		print_ants(anthill, routes);
	}
	delete_anthill(anthill, -1);
	free_path(routes);
	free_data(data);
	ft_strdel(&graph);
}

static int			open_log_file(void)
{
	int	ret;

	ret = open("log_file", O_CREAT | O_TRUNC | O_RDWR,
			S_IRUSR | S_IWUSR);
	if (ret == -1)
		return (NO);
	return (ret);
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
	data = init_struct();
	if (!(graph = create_file(data)))
		return (0);
	if (!(anthill = parse_anthill(graph, data, anthill)))
		return (0);
	if (verbose == YES)
	{
		verbose = open_log_file();
		print_anthill_log(verbose, anthill);
	}
	routes = find_best_routes(anthill, routes, verbose);
	if (verbose != NO)
		close(verbose);
	print_clean(graph, anthill, routes, data);
	return (0);
}
