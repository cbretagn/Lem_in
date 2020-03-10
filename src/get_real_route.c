/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:04:45 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 16:22:44 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#include <limits.h>

static int			next_room(t_dynode *path, t_anthill *anthill)
{
	int		curr;
	int		prev;

	curr = path->tab[path->size - 1];
	prev = path->tab[path->size - 2];
	if (anthill->nodes[curr]->tab[0] == prev)
		return (anthill->nodes[curr]->tab[1]);
	return (anthill->nodes[curr]->tab[0]);
}

static int			find_from(int start, int to, t_anthill *anthill)
{
	int		i;
	int		dist;
	int		ret;

	i = -1;
	dist = INT_MAX;
	ret = -1;
	while (++i < anthill->connectors[start]->size)
	{
		if (anthill->connectors[start]->tab[i].name == to
				&& anthill->connectors[start]->tab[i].dist < dist)
		{
			ret = anthill->connectors[start]->tab[i].from;
			dist = anthill->connectors[start]->tab[i].dist;
		}
	}
	return (ret);
}

static t_dynode		*get_full_direct(t_dynode *original, t_anthill *anthill,
						t_dynode *new)
{
	int		push;

	new = push_int(new, anthill->start);
	push = original->tab[2];
	while (push != anthill->end)
	{
		new = push_int(new, push);
		push = next_room(new, anthill);
	}
	new = push_int(new, push);
	return (new);
}

static t_dynode		*get_full_route(t_dynode *original, int size,
						t_anthill *anthill, t_dynode *new)
{
	int		i;
	int		push;

	i = size;
	new = push_int(new, anthill->start);
	while (--i > 0)
	{
		push = find_from(original->tab[i], original->tab[i - 1], anthill);
		new = push_int(new, push);
		if (push != original->tab[i - 1])
		{
			while (push != original->tab[i - 1])
			{
				push = next_room(new, anthill);
				new = push_int(new, push);
			}
		}
	}
	return (new);
}

t_path				*get_real_routes(t_path *routes, t_anthill *anthill)
{
	int				i;
	t_dynode		*new_route;
	t_dynode		*tmp;

	i = -1;
	while (++i < routes->size)
	{
		if (!(new_route = create_dynode(BASE_DYN_NODES)))
			exit(-1);
		if (routes->tab[i]->tab[0] == DIRECT)
			new_route = get_full_direct(routes->tab[i], anthill, new_route);
		else
			new_route = get_full_route(routes->tab[i], routes->tab[i]->size,
						anthill, new_route);
		tmp = routes->tab[i];
		routes->tab[i] = new_route;
		delete_dynode(tmp);
		new_route = NULL;
	}
	return (routes);
}
