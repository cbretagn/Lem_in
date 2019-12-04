/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:07:52 by cbretagn          #+#    #+#             */
/*   Updated: 2019/12/04 17:05:47 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		get_nb_paths(t_path *routes, int nb_ants)
{
	int		ret;
	int		i;
	int		j;
	int		tmp;

	ret = 1;
	i = 0;
	while (++i < routes->size)
	{
		j = i;
		tmp = nb_ants;
		while (--j >= 0)
			tmp -= (routes->path_length[i] - routes->path_length[j]);
		if (tmp < 1)
			break ;
		ret++;
	}
	return (ret);
}

t_path			*get_nb_ants(t_path *routes, int nb_ants)
{
	int		nb_path;
	int		i;
	int		tmp;

	nb_path = get_nb_paths(routes, nb_ants);
	printf("nb paths to use is %d\n", nb_path);
	i = 0;
	while (++i < routes->size)
		routes->nb_ants[i] = 0;
	if (nb_path > 1)
	{
		i = nb_path - 1;
		while (--i >= 0)
		{
			tmp = (routes->path_length[nb_path - 1] - routes->path_length[i]);
			routes->nb_ants[i] += tmp;
			nb_ants -= tmp;
		}
		routes->nb_ants[nb_path - 1] = 1;
		nb_ants -= 1;
		while (nb_ants > 0)
		{
			i = -1;
			while (++i < nb_path)
			{
				routes->nb_ants[i]++;
				nb_ants--;
				if (nb_ants < 1)
					break ;
			}
		}
	}
	else
		routes->nb_ants[0] = nb_ants;
	return (routes);
}
