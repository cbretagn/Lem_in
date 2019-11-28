/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_del_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:09:15 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/28 14:34:29 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_dynode	*create_dynode(int capacity)
{
	t_dynode	*node;

	if (!(node = (t_dynode *)malloc(sizeof(t_dynode))))
		return (NULL);
	node->cap = capacity;
	node->size = 0;
	if (!(node->tab = (t_vert *)malloc(sizeof(t_vert) * capacity)))
	{
		free(node);
		node = NULL;
		return (NULL);
	}
	return (node);
}

t_dynode	*push_int(t_dynode *node, int nb)
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
		{
			node->tab[i].name = tmp->tab[i].name;
			node->tab[i].vis = 0;
			node->tab[i].dist = INT_MAX;
			node->tab[i].pred = -1;
		}
		node->tab[i].name = nb;
		node->tab[i].vis = 0;
		node->tab[i].dist = INT_MAX;
		node->tab[i].pred = -1;
		node->size = tmp->size + 1;
		delete_dynode(tmp);
	}
	else
	{
		node->tab[node->size].name = nb;
		node->tab[node->size].vis = 0;
		node->tab[node->size].dist = INT_MAX;
		node->tab[node->size].pred = -1;
		node->size++;
	}
	return (node);
}

void		delete_dynode(t_dynode *node)
{
	free(node->tab);
	node->tab = NULL;
	free(node);
	node = NULL;
}

t_anthill	*create_anthill(int	size, t_data *data)
{
	t_anthill	*ret;
	int			i;

	if (!(ret = (t_anthill *)malloc(sizeof(t_anthill))))
		exit(-2);
	if (!(ret->rooms = (char **)malloc(sizeof(char *) * size)))
		exit(-2);
	ret->ants = data->ants;
	ret->start = 0;
	ret->end = 0;
	i = -1;
	while (++i < size)
		ret->rooms[i] = NULL;
	if (!(ret->nodes = (t_dynode **)malloc(sizeof(t_dynode *) * size)))
		exit(-2);
	i = -1;
	while (++i < size)
		ret->nodes[i] = create_dynode(BASE_DYN_NODES);
	ret->nb_room = size;
	if (!(ret->connectors = (t_connector **)malloc(sizeof(t_connector *) * size)))
		exit(-2);
	i = -1;
	while (++i < size)
		ret->connectors[i] = NULL;
	return (ret);
}

//add delete connector to delete anthill
void		delete_anthill(t_anthill *anthill)
{
	int	 i;

	i = -1;
	while (++i < anthill->nb_room)
		ft_strdel(&anthill->rooms[i]);
	free(anthill->rooms);
	anthill->rooms = NULL;
	i = -1;
	while (++i < anthill->nb_room)
		delete_dynode(anthill->nodes[i]);
	free(anthill->nodes);
	anthill->nodes = NULL;
	free(anthill);
	anthill = NULL;
}
