/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector_graph_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:00:30 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 16:05:09 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_connector					*create_connector(int size)
{
	t_connector	*ret;
	int			i;

	i = -1;
	if (!(ret = (t_connector *)malloc(sizeof(t_connector))))
		exit(-2);
	ret->size = 0;
	ret->cap = size;
	if (!(ret->tab = (t_vertex *)malloc(sizeof(t_vertex) * size)))
		exit(-2);
	return (ret);
}

void						delete_connector(t_connector *del)
{
	free(del->tab);
	del->tab = NULL;
	free(del);
	del = NULL;
}

static t_connector			*fill_vertex(t_connector *c, int i, t_vertex v)
{
	c->tab[i].name = v.name;
	c->tab[i].dist = v.dist;
	c->tab[i].from = v.from;
	return (c);
}

t_connector					*push_vertex(t_connector *connector,
								int room, int distance, int first_node)
{
	t_connector		*tmp;
	int				i;

	i = -1;
	if (connector->cap == connector->size)
	{
		tmp = connector;
		if (!(connector = create_connector(tmp->cap * 2)))
			exit(-2);
		while (++i < tmp->size)
			connector = fill_vertex(connector, i, tmp->tab[i]);
		connector->tab[tmp->size].name = room;
		connector->tab[tmp->size].dist = distance;
		connector->tab[tmp->size].from = first_node;
		connector->size = tmp->size + 1;
		delete_connector(tmp);
		return (connector);
	}
	connector->tab[connector->size].name = room;
	connector->tab[connector->size].dist = distance;
	connector->tab[connector->size].from = first_node;
	connector->size++;
	return (connector);
}
