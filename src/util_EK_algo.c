/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_EK_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:16:14 by sadahan           #+#    #+#             */
/*   Updated: 2020/02/13 13:14:00 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

// static int		*fill_distance(t_anthill *a)
// {
// 	int			*dist;
// 	t_pile		*queue;
// 	int			u;
// 	int			v;
// 	int			i;
// 	int			*visited;
// 	int			dist;

// 	i = -1;
// 	if (!(dist = (int *)malloc(sizeof(int) * a->nb_room)))
// 		exit(-2);
// 	if (!(visited = (int *)malloc(sizeof(int) * a->nb_room)))
// 		exit(-2);
// 	while (++i < a->nb_room)
// 	{
// 		dist[i] = 10000;
// 		visited[i] = -1;
// 	}
// 	dist[a->end] = 0;
// 	visited[a->end] = 0;
// 	if (!(queue = init_pile(a->end)))
// 		exit(-2);
// 	while (queue->nb_elem > 0)
// 	{
// 		i = -1;
// 		u = del_bottom(queue);
// 		while (++i < a->nodes[u]->size)
// 		{
// 			v = a->nodes[u]->tab[i];
// 			if (dist[v] > dist[u] + 1)
// 				dist[v] = dist[u] + 1;
// 			if (visited[v] == -1)
// 			{
// 				visited[v] = 1;
// 				if (v != a->start)
// 				{
// 					if (queue->nb_elem > 0)
// 						add_to_top(queue, v);
// 					else
// 						queue = init_pile(v);
// 				}
// 				else
// 					return (1);
// 			}
// 		}
// 	}
// 	return (dist);
// }

static t_dynode	**bfs_false_nodes(t_anthill *a, t_dynode **nodes, int *visited)
{
	t_pile		*queue;
	int			u;
	int			v;
	int			i;
	// int			*dist;

	// dist = fill_distance(a);
	if (!(queue = init_pile(a->start)))
		exit(-2);
	i = -1;
	while (++i < a->nodes[a->start]->size)
	{
		nodes[a->start] = push_int(nodes[a->start], a->nodes[a->start]->tab[i]);
		// nodes[a->nodes[a->start]->tab[i]] = push_int(nodes[a->nodes[a->start]->tab[i]], a->start);
	}
	visited[a->start] = 0;
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		if (u != a->start)
		{
			// printf("u = %d\n", u);
			nodes[u] = push_int(nodes[u], u + a->nb_room);
			nodes[u + a->nb_room] = push_int(nodes[u + a->nb_room], u);
			visited[u] = 0;
		}
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
			// printf("v = %d\n", v);
			if (visited[v] == -1)
			{
				// visited[v] = 0;
				// printf("queued\n");
				if (u != a->start)
				{
					nodes[v] = push_int(nodes[v], u + a->nb_room);
					nodes[u + a->nb_room] = push_int(nodes[u + a->nb_room], v);
				}
				if (v != a->end)
				{
					if (queue->nb_elem > 0)
						add_to_top(queue, v);
					else
						queue = init_pile(v);
				}
			}
		}
	}
	return (nodes);
}

t_dynode		**create_false_nodes(t_anthill *a)
{
	t_dynode	**false_nodes;
	int			i;
	int			*visited;
	
	if (!(visited = init_parent(a)))
		exit(-2);
	if (!(false_nodes = (t_dynode **)malloc(sizeof(t_dynode *) * a->nb_room *2)))
		exit(-2);
	i = -1;
	while (++i < a->nb_room * 2)
		false_nodes[i] = create_dynode(BASE_DYN_NODES);
	false_nodes = bfs_false_nodes(a, false_nodes, visited);
	return (false_nodes);
}

int	**init_matrice(int size)
{
	int		**m;
	int		i;
	int		j;

	i = -1;
	if (!(m = (int **)malloc(sizeof(int *) * size)))
		exit (-2);
	while (++i < size)
	{
		if (!(m[i] = (int *)malloc(sizeof(int) * size)))
			exit(-2);
		j = -1;
		while (++j < size)
			m[i][j] = 1;
	}
	return (m);
}

int		*init_parent(int size)
{
	int *parent;
	int	i;

	i = -1;
	if (!(parent = (int *)malloc(sizeof(int) * size)))
		exit(-2);
	while (++i < size)
		parent[i] = -1;
	parent[a->start] = -2;
	return (parent);
}