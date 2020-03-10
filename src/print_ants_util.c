/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:06:01 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 17:17:58 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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
	s = puhs_str(s, " ");
	return (s);
}
