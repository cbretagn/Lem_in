/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:53:53 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 17:48:42 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_dstring	*display_swarm(t_ants *swarm, t_anthill *anthill,
							t_dstring *s)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_itoa(swarm->nb_lines);
	s = push_str(s, "\033[1;36m");
	s = push_str(s, tmp);
	s = push_str(s, "\033[0m");
	ft_strdel(&tmp);
	s = push_str(s, " ");
	while (++i < anthill->ants)
	{
		if (swarm->room[i] == anthill->end && swarm->curr[i] == -2)
			continue ;
		if (swarm->curr[i] != -1 && swarm->path[i] != -1)
			s = push_ant_str(s, i, swarm, anthill);
		if (swarm->room[i] == anthill->end)
			swarm->curr[i] = -2;
	}
	s = push_str(s, "\n");
	swarm->nb_lines++;
	return (s);
}

static void			push_ant(t_ants *swarm, t_path *routes,
						t_anthill *anthill, int i)
{
	swarm->curr[i] += 1;
	swarm->room[i] = routes->tab[swarm->path[i]]->tab[swarm->curr[i]];
	if (swarm->room[i] == anthill->end)
		swarm->arrived += 1;
}

static t_ants		*init_table(t_ants *swarm, int size)
{
	int		i;

	i = -1;
	if (!(swarm = (t_ants *)malloc(sizeof(t_ants))))
		exit(-1);
	if (!(swarm->path = (int *)malloc(sizeof(int) * size)))
		exit(-1);
	if (!(swarm->curr = (int *)malloc(sizeof(int) * size)))
		exit(-1);
	if (!(swarm->room = (int *)malloc(sizeof(int) * size)))
		exit(-1);
	while (++i < size)
	{
		swarm->path[i] = -1;
		swarm->curr[i] = -1;
		swarm->room[i] = -1;
	}
	swarm->arrived = 0;
	swarm->nb_lines = 1;
	return (swarm);
}

static void			push_in_path(t_path *routes, t_ants *swarm,
						t_anthill *anthill, int i)
{
	int		j;

	j = -1;
	while (++j < swarm->path_to_use && swarm->arrived != anthill->ants)
	{
		if (routes->nb_ants[j] > 0 || routes->tab[j]->tab[1] == anthill->end)
		{
			swarm->path[i] = j;
			swarm->curr[i] = 1;
			swarm->room[i] = routes->tab[j]->tab[1];
			routes->nb_ants[j] -= 1;
			if (swarm->room[i] == anthill->end)
			{
				j -= 1;
				swarm->arrived++;
			}
			i++;
		}
	}
}

void				print_ants(t_anthill *anthill, t_path *routes)
{
	t_ants		*swarm;
	int			i;
	t_dstring	*s;

	swarm = NULL;
	swarm = init_table(swarm, anthill->ants);
	swarm->path_to_use = nb_path_to_use(routes);
	if (!(s = create_dstring(BUFFER_SIZE, "")))
		exit(-1);
	while (swarm->arrived != anthill->ants)
	{
		i = -1;
		while (++i < anthill->ants && swarm->path[i] != -1)
		{
			if (swarm->room[i] == anthill->end)
				continue ;
			push_ant(swarm, routes, anthill, i);
		}
		if (i < anthill->ants)
			push_in_path(routes, swarm, anthill, i);
		s = display_swarm(swarm, anthill, s);
	}
	ft_putstr(s->str);
	delete_dstring(s);
	free_swarm(swarm);
}
