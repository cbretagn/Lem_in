/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_routes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:20:47 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/20 16:34:44 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_path	*replace_routes(t_path *routes, int i, t_anthill *anthill)
{
	t_dynode	*tmp;
	int			j;
	int			push;
	int			size;

	size = 0;
	if (!(tmp = create_dynode(BASE_DYNODE)))
		exit(-1);
	j = 0;
	while (j < routes->tab[i]->size)
	{
		if (routes->tab[i]->tab[j] > anthill->nb_room)
		{
			size++;
			continue ;
		}
		else
		{
			tmp = push_int(tmp, routes->tab[i]->tab[j]);
			if (routes->tab[i]->tab[j] == anthill->end)
				break ;
			push = routes->tab[i]->tab[j + 1];
			while (push != routes->tab[i]->tab[j + 2])
			{
				push = next_room(anthill, 
			}
	}
}

t_path			*get_real_routes(t_path *routes, t_anthill *anthill)
{
	int		i;

	i = -1;
	while (++i < routes->size)
	{
		routes = replace_route(routes, i, anthill);
	}
	return (routes);
}
