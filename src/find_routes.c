/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_routes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:54:39 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/10 19:05:46 by sadahan          ###   ########.fr       */
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

static t_path	*get_ek1_routes(t_anthill *anthill, t_path *routes)
{
	routes = edmonds_karp1(anthill);
	routes = get_nb_ants(routes, anthill->ants);
	return (routes);
}

static t_path	*get_ek2_routes(t_anthill *anthill, t_path *routes)
{
	routes = edmonds_karp2(anthill);
	routes = get_nb_ants(routes, anthill->ants);
	return (routes);
}

t_path			*find_best_routes(t_anthill *anthill, t_path *routes_djk)
{
	t_path		*routes_ek1;
	t_path		*routes_ek2;
	int			lines_ek1;
	int			lines_ek2;
	int			lines_djk;

	routes_ek1 = NULL;
	routes_ek2 = NULL;
	routes_djk = get_dijkstra_routes(anthill, routes_djk);
	lines_djk = nb_lines(routes_djk);
	routes_ek1 = get_ek1_routes(anthill, routes_ek1);
	lines_ek1 = nb_lines(routes_ek1);
	routes_ek2 = get_ek2_routes(anthill, routes_ek2);
	lines_ek2 = nb_lines(routes_ek2);
	if (lines_djk > 0 && lines_djk <= lines_ek1 && lines_djk <= lines_ek2)
		return (routes_djk);
	else if (lines_ek1 > 0 && lines_ek1 <= lines_ek2)
		return (routes_ek1);
	else if (lines_ek2 > 0)
		return (routes_ek2);
	else
		return (NULL);
}
