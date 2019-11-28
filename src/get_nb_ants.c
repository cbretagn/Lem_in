/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:07:52 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/28 18:09:18 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_path			*get_nb_ants(t_path *routes, int nb_ants)
{
	int		x;
	int		sub;
	int		i;

	if (nb_ants == 1)
	{
		routes->nb_ants[0] = 1;
		routes->nb_ants[1] = 0;
		return (routes);
	}
	ft_putstr("hey\n");
	x = nb_ants;
	i = routes->size - 1;
	while (--i > 0)
	{
		sub = ((routes->path_length[i] - routes->path_length
					[i - 1]) * (routes->size - 1 - i));
		x += sub;
	}
	x /= (routes->size - 1);
	printf("x is %d\n", x);
	routes->nb_ants[0] = x;
	i = 0;
	while (++i < routes->size - 1)
	{
		x = x - (routes->path_length[i] - routes->path_length[i - 1]);
		routes->nb_ants[i] = x;
	}
	routes->nb_ants[i] = 0;
	return (routes);
}
