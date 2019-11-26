/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector_graph_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:00:30 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/26 11:21:22 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_connector		*create_connector(int size)
{
	t_connector	*ret;
	int			i;

	i = -1;
	if (!(ret = (t_connector *)malloc(sizeof(t_connector))))
		exit(-2);
	ret->size = 0;
	ret->cap = size;
	ret->xflow = 0;
	ret->height = 0;
	if (!(ret->tab = (t_vertex *)malloc(sizeof(t_vertex) * size)))
			exit(-2);
	return (ret);
}

void			delete_connector(t_connector *del)
{
	free(del->tab);
	del->tab = NULL;
	free(del);
	del = NULL;
}

t_connector		*push_vertex(t_connector *connector, int room, int distance)
{
	t_connector		*tmp;
	int				i;

	i = -1;
	if (connector->cap == connector->size)
	{
		tmp = connector;
		if (!(connector = create_connector(tmp->cap * 2)))
			exit (-2);
		while (++i < tmp->size)
		{
			connector->tab[i].name = tmp->tab[i].name;
			connector->tab[i].dist = tmp->tab[i].dist;
			connector->tab[i].flow = 0;
			// connector->tab[i].xflow = 0;
			connector->tab[i].cap_flow = tmp->tab[i].dist;
			// connector->tab[i].height = 0;
		}
		// connector->tab[tmp->size].name = room;
		// connector->tab[tmp->size].dist = distance;
		// connector->tab[tmp->size].flow = 0;
		// connector->tab[tmp->size].xflow = 0;
		// connector->tab[tmp->size].cap = 0;
		// connector->tab[tmp->size].height = 0;
		// connector->size = tmp->size + 1;
		delete_connector(tmp);
		// return (connector);
	}
	connector->tab[connector->size].name = room;
	connector->tab[connector->size].dist = distance;
	connector->tab[connector->size].flow = 0;
	// connector->tab[connector->size].xflow = 0;
	connector->tab[connector->size].cap_flow = distance;
	// connector->tab[connector->size].height = 0;
	connector->size++;
	return (connector);
}
