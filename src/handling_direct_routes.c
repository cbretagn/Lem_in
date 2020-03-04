/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_direct_routes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:33:19 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/27 16:57:35 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int			is_visited(int node, t_dynode *list)
{
	int		i;

	i = -1;
	while (++i < list->size)
	{
		if (list->tab[i] == node)
			return (1);
	}
	return (0);
}

t_path		*get_direct_path(t_path *routes, t_anthill *anthill)
{
	int				i;
	t_connector		*start;
	int				path;

	path = routes->size;
	i = -1;
	start = anthill->connectors[anthill->start];
	while (++i < start->size)
	{
		if (start->tab[i].name == anthill->end)
		{
			routes->tab[path] = push_int(routes->tab[path], DIRECT);
			routes->tab[path] = push_int(routes->tab[path], start->tab[i].name);
			routes->tab[path] = push_int(routes->tab[path], start->tab[i].from);
			routes->path_length[path] = start->tab[i].dist;
			routes->size++;
			path++;
		}
	}
	return (routes);
}
