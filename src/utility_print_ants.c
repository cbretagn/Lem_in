/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_print_ants.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:59:23 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 17:26:10 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int	get_next_nb_ants(t_path *routes, int i)
{
	while (++i < routes->size)
	{
		if (routes->nb_ants[i] > 0)
			return (routes->nb_ants[i]);
	}
	return (1);
}

int			nb_path_to_use(t_path *routes)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while (++i < routes->size)
	{
		if (routes->nb_ants[i] > 0)
			ret++;
	}
	if (routes->nb_ants[ret - 1] == 0)
		routes->nb_ants[ret - 1] = get_next_nb_ants(routes, ret - 1);
	return (ret);
}

t_dstring	*push_ant_str(t_dstring *s, int nb, t_ants *swarm,
					t_anthill *anthill)
{
	char	*tmp;

	s = push_str(s, "L");
	tmp = ft_itoa(nb + 1);
	s = push_str(s, tmp);
	ft_strdel(&tmp);
	s = push_str(s, "-");
	s = push_str(s, anthill->rooms[swarm->room[nb]]);
	s = push_str(s, " ");
	return (s);
}
