/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_del_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <cbretagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:09:15 by cbretagn          #+#    #+#             */
/*   Updated: 2020/04/27 14:58:11 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_dynode		*create_dynode(int capacity)
{
	t_dynode	*node;

	if (!(node = (t_dynode *)malloc(sizeof(t_dynode))))
		exit(-2);
	node->cap = capacity;
	node->size = 0;
	if (!(node->tab = (int *)malloc(sizeof(int) * capacity)))
		exit(-2);
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
	ret->nodes = create_node_tab(size * 2);
	ret->inter_nodes = create_node_tab(size * 2);
	ret->nb_room = size;
	if (!(ret->connectors = malloc(sizeof(t_connector *) * size)))
		exit(-2);
	i = -1;
	while (++i < size)
		ret->connectors[i] = NULL;
	return (ret);
}

void			delete_anthill(t_anthill *anthill, int i)
{
	while (++i < anthill->nb_room)
		ft_strdel(&anthill->rooms[i]);
	free(anthill->rooms);
	anthill->rooms = NULL;
	i = -1;
	while (++i < anthill->nb_room * 2)
	{
		delete_dynode(anthill->nodes[i]);
		delete_dynode(anthill->inter_nodes[i]);
	}
	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!anthill->connectors[i])
			continue ;
		delete_connector(anthill->connectors[i]);
	}
	free(anthill->connectors);
	anthill->connectors = NULL;
	free(anthill->nodes);
	anthill->nodes = NULL;
	free(anthill->inter_nodes);
	anthill->inter_nodes = NULL;
	free(anthill);
	anthill = NULL;
}
