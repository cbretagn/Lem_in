/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_routes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:54:39 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/12 19:25:11 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_path	*get_dijkstra_routes(t_anthill *anthill, t_path *routes)
{
	routes = next_shortest_path(anthill);
	routes = get_direct_path(routes, anthill);
	routes = get_nb_ants(routes, anthill->ants);
	routes = get_real_routes(routes, anthill);
	return (routes);
}

static t_path	*get_ek1_routes(t_anthill *anthill, t_path *routes, int l,
						int fd)
{
	t_path		*routes_ek1;
	int			lines_ek1;

	routes_ek1 = NULL;
	routes_ek1 = edmonds_karp1(anthill);
	if (!routes_ek1)
		return (routes);
	routes_ek1 = get_nb_ants(routes_ek1, anthill->ants);
	lines_ek1 = nb_lines(routes_ek1);
	print_routes_log(fd, routes_ek1, lines_ek1, "Edmond Karps :\n");
	if (l == 0 || (lines_ek1 > 0 && lines_ek1 < l))
	{
		free_path(routes);
		return (routes_ek1);
	}
	free_path(routes_ek1);
	return (routes);
}

static t_path	*get_ek2_routes(t_anthill *anthill, t_path *routes, int l,
						int fd)
{
	t_path		*routes_ek2;
	int			lines_ek2;

	routes_ek2 = NULL;
	routes_ek2 = edmonds_karp2(anthill);
	if (!routes_ek2)
		return (routes);
	routes_ek2 = get_nb_ants(routes_ek2, anthill->ants);
	lines_ek2 = nb_lines(routes_ek2);
	print_routes_log(fd, routes_ek2, lines_ek2, 
			"Edmond Karps with intermediary nodes :\n");
	if (l == 0 || (lines_ek2 > 0 && lines_ek2 < l))
	{
		free_path(routes);
		return (routes_ek2);
	}
	free_path(routes_ek2);
	return (routes);
}

t_path			*find_best_routes(t_anthill *anthill, t_path *routes, int fd)
{
	int			lines;

	routes = get_dijkstra_routes(anthill, routes);
	lines = routes == NULL ? 0 : nb_lines(routes);
	print_routes_log(fd, routes, lines, "Djikstra :\n");
	routes = get_ek1_routes(anthill, routes, lines, fd);
	lines = routes == NULL ? 0 : nb_lines(routes);
	routes = get_ek2_routes(anthill, routes, lines, fd);
	return (routes);
}
