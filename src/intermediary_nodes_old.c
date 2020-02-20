/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intermediary_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:27:55 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/20 15:43:07 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

//double connector size
//

static int		next_free_node(t_anthill *anthill, int to_replace)
{
	int		i;

	i = to_replace + anthill->nb_room;
	if (anthill->connectors[i] == NULL)
		return (i);
	while (++i < anthill->nb_room * 2)
	{
		if (anthill->connectors[i] == NULL)
			return (i);
	}
	i = anthill->nb_room;
	while (i < to_replace)
	{
		if (anthill->connectors[i] == NULL)
			return (i);
		i++;
	}
	return (-1);
}

static int		check_double(t_connector *hub, int node)
{
	int		nb;
	int		i;

	nb = 0;
	i = -1;
	while (++i < hub->size)
	{
		if (hub->tab[i].name == node)
			nb++;
	}
	if (nb > 1)
		return (node);
	return (-1);
}

static t_anthill	*copy_vertex(int connect, int dst, int src,
							t_anthill *anthill)
{
	anthill->connectors[connect]->tab[dst].name = 
		anthill->connectors[connect]->tab[src].name;
	anthill->connectors[connect]->tab[dst].from = 
		anthill->connectors[connect]->tab[src].from;
	anthill->connectors[connect]->tab[dst].dist = 
		anthill->connectors[connect]->tab[src].dist;
	return (anthill);
}

static t_anthill	*connect_intermediary(t_anthill *anthill, int to, int new,
						int from)
{
	int		i;
	int		j;
	int		del;

	i = -1;
	del = -1;
	while (++i < anthill->connectors[to]->size)
	{
		if (anthill->connectors[to]->tab[i].name == from && del == -1)
		{
			anthill->connectors[to]->tab[i].name = new;
			anthill->connectors[to]->tab[i].from = new;
			anthill->connectors[to]->tab[i].dist = 1;
			del++;
		}
		if (anthill->connectors[to]->tab[i].name == from && del == 0)
			break ;
	}
	j = i;
	while (j < anthill->connectors[to]->size)
	{
		while (anthill->connectors[to]->tab[j].name == from 
				&& j < anthill->connectors[to]->size)
		{
			del++;
			j++;
		}
		if (j >= anthill->connectors[to]->size)
			break ;
		while (anthill->connectors[to]->tab[j].name != from 
				&& j < anthill->connectors[to]->size)
		{
			anthill = copy_vertex(to, i, j, anthill);
			i++;
			j++;
		}
	}
	anthill->connectors[to]->size -= del;
	return (anthill);
}

static t_anthill	*add_node(t_anthill *anthill, int to, t_connector *hub,
							int from)
{
	int				i;
	int				new;
	int				new2;

	new = next_free_node(anthill, from);
	if (new == -1)
	{
		printf("uh we have a problem here\n");
		exit(-2);
	}
	if (!(anthill->connectors[new] = create_connector(BASE_CONNECTORS)))
		exit(-1);
	new2 = next_free_node(anthill, from);
	if (new2 == -1)
	{
		printf("uh we have a problem here\n");
		exit(-2);
	}
	if (!(anthill->connectors[new2] = create_connector(BASE_CONNECTORS)))
		exit(-1);
	anthill->connectors[new] = push_vertex(anthill->connectors[new], to, 1, new);
	anthill->connectors[new2] = push_vertex(anthill->connectors[new2], from, 1, new);
	i = -1;
	while (++i < hub->size)
	{
		if (hub->tab[i].name == to)
		{
			anthill->connectors[new] = push_vertex(anthill->connectors[new],
					new2, hub->tab[i].dist - 1, hub->tab[i].from);
			anthill->connectors[new2] = push_vertex(anthill->connectors[new2],
					new, hub->tab[i].dist - 1, hub->tab[i].from);
		}
	}
	anthill = connect_intermediary(anthill, to, new, from);
	anthill = connect_intermediary(anthill, from, new2, to);
	return (anthill);
}

t_anthill			*add_intermediary_nodes(t_anthill *anthill)
{
	int			i;
	int			j;
	int			to;
	int			count;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!anthill->connectors[i] || i == anthill->end)
			continue ;
		j = -1;
		count = 0;
		while (++j < anthill->connectors[i]->size)
		{
			if (anthill->connectors[i]->tab[j].name == anthill->end)
				continue ;
			to = check_double(anthill->connectors[i], 
					anthill->connectors[i]->tab[j].name);
			if (to > -1 && to < anthill->nb_room)
			{
				anthill = add_node(anthill, to, anthill->connectors[i], i);
				count++;
			}
		}
	}
	return (anthill);
}
