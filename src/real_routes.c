/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_routes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:20:47 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/21 16:56:03 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		next_room(t_anthill *anthill, int push, t_dynode *route)
{
	printf("%d\n", route->tab[route->size - 2]);
	if (anthill->nodes[push]->tab[0] == route->tab[route->size - 2])
		return (anthill->nodes[push]->tab[1]);
	return (anthill->nodes[push]->tab[0]);
}

static t_path	*replace_routes(t_path *routes, int i, t_anthill *anthill)
{
	t_dynode	*tmp;
	int			j;
	int			push;
	int			size;

	size = 0;
	if (!(tmp = create_dynode(BASE_DYN_NODES)))
		exit(-1);
	j = 0;
	while (j < routes->tab[i]->size)
	{
		if (routes->tab[i]->tab[j] > anthill->nb_room)
			size++;
		else
		{
			push = routes->tab[i]->tab[j + 1];
			tmp = push_int(tmp, push);
			if (push == anthill->end)
				break ;
			while (push != routes->tab[i]->tab[j])
			{
				printf("pushing %d\n", push);
				push = next_room(anthill, push, routes->tab[i]);
				tmp = push_int(tmp, push);
			}
		}
		j += 2;
	}
	delete_dynode(routes->tab[i]);
	routes->tab[i] = tmp;
	routes->path_length[i] -= size;
	return (routes);
}

t_path			*get_real_routes(t_path *routes, t_anthill *anthill)
{
	int		i;

	i = -1;
	while (++i < routes->size)
	{
		routes = replace_routes(routes, i, anthill);
	}
	return (routes);
}
