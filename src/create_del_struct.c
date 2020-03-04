/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_del_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:09:15 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/25 14:14:21 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_dynode		*create_dynode(int capacity)
{
	t_dynode	*node;

	if (!(node = (t_dynode *)malloc(sizeof(t_dynode))))
		return (NULL);
	node->cap = capacity;
	node->size = 0;
	if (!(node->tab = (int *)malloc(sizeof(int) * capacity)))
	{
		exit(-1);
	}
	return (node);
}

t_dynode		*push_int(t_dynode *node, int nb)
{
	t_dynode	*tmp;
	int			i;

	i = -1;
	if (node->size >= node->cap)
	{
		tmp = node;
		if (!(node = create_dynode(tmp->cap * 2)))
		{
			delete_dynode(tmp);
			return (NULL);
		}
		while (++i < tmp->size)
			node->tab[i] = tmp->tab[i];
		node->tab[i] = nb;
		node->size = tmp->size + 1;
		delete_dynode(tmp);
	}
	else
	{
		node->tab[node->size] = nb;
		node->size++;
	}
	return (node);
}

void			delete_dynode(t_dynode *node)
{
	free(node->tab);
	node->tab = NULL;
	free(node);
	node = NULL;
}

t_anthill		*create_anthill(int size)
{
	t_anthill	*ret;
	int			i;

	if (!(ret = (t_anthill *)malloc(sizeof(t_anthill))))
		exit(-2);
	if (!(ret->rooms = (char **)malloc(sizeof(char *) * size)))
		exit(-2);
	i = -1;
	while (++i < size)
		ret->rooms[i] = NULL;
	if (!(ret->nodes = (t_dynode **)malloc(sizeof(t_dynode *) * size)))
		exit(-2);
	i = -1;
	while (++i < size)
		ret->nodes[i] = create_dynode(BASE_DYN_NODES);
	ret->nb_room = size;
	if (!(ret->connectors = malloc(sizeof(t_connector *) * size)))
		exit(-2);
	i = -1;
	while (++i < size)
		ret->connectors[i] = NULL;
	return (ret);
}

void			delete_anthill(t_anthill *anthill)
{
	int			i;
	int			co;

	i = -1;
	co = 0;
	while (++i < anthill->nb_room)
		ft_strdel(&anthill->rooms[i]);
	free(anthill->rooms);
	anthill->rooms = NULL;
	i = -1;
	while (++i < anthill->nb_room)
	{
		if (anthill->nodes[i]->size > 2)
			co++;
		delete_dynode(anthill->nodes[i]);
	}
	i = -1;
	while (++i < co)
		delete_connector(anthill->connectors[i]);
	free(anthill->connectors);
	anthill->connectors = NULL;
	free(anthill->nodes);
	anthill->nodes = NULL;
	free(anthill);
	anthill = NULL;
}
