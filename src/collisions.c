/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:13:01 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/12 15:54:05 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

static void	check_path(t_path *routes, int curr_path, int curr_room, int end)
{
	int		i;
	int		j;
	int		del;

	i = -1;
	while (++i < routes->size)
	{
		if (i == curr_path)
			continue ;
		j = 0;
		while (j < routes->tab[i]->size)
		{
			if (routes->tab[i]->tab[j] != end 
					&& routes->tab[i]->tab[j] == curr_room)
			{
				del = routes->path_length[i] > routes->path_length[curr_path] ?
					i : curr_path;
				routes->path_length[del] = INT_MAX;
			}
			j +=2;
		}
	}
}

t_path		*handle_collision(t_path *routes, t_anthill *anthill)
{
	int		i;
	int		j;

	i = -1;
	while (++i < routes->size)
	{
		j = 0;
		while (j < routes->tab[i]->size)
		{
			check_path(routes, i, routes->tab[i]->tab[j], anthill->end);
			j += 2;
		}
	}
	return (routes);
}
