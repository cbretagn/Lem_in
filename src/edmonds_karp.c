/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:13:09 by sadahan           #+#    #+#             */
/*   Updated: 2020/02/13 13:13:59 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		bfs(t_anthill *a, int **res, int *parent, t_dynode **nodes)
{
	t_pile		*queue;
	int			u;
	int			v;
	int			i;

	if (!(queue = init_pile(a->start)))
		exit(-2);
	i = -1;
	while (++i < a->nb_room * 2)
		parent[i] = -1;
	parent[a->start] = -2;
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		while (++i < nodes[u]->size)
		{
			v = nodes[u]->tab[i];
			if (res[u][v] > 0 && parent[v] == -1)
			{
				parent[v] = u;
				if (v != a->end)
				{
					if (queue->nb_elem > 0)
						add_to_top(queue, v);
					else
						queue = init_pile(v);
				}
				else
					return (1);
			}
		}
	}
	return (0);
}


static int		bfs_paths(t_anthill *a, int **res, int *parent, t_dynode **nodes)
{
	t_pile		*queue;
	int			u;
	int			v;
	int			i;

	if (!(queue = init_pile(a->start)))
		exit(-2);
	i = -1;
	while (++i < a->nb_room * 2)
		parent[i] = -1;
	parent[a->start] = -2;
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		while (++i < nodes[u]->size)
		{
			v = nodes[u]->tab[i];
			if (res[u][v] == 0 && parent[v] == -1)
			{
				parent[v] = u;
				if (v != a->end)
				{
					if (queue->nb_elem > 0)
						add_to_top(queue, v);
					else
						queue = init_pile(v);
				}
				else
					return (1);
			}
		}
	}
	return (0);
}

void			print_matrix(int **res, int size)
{
	int			i;
	int			j;

	printf("\n");
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			printf("%d\t", res[i][j]);
		printf("\n");
	}
}

static t_path	*save_paths(t_anthill *a, int **res, t_path *path, t_dynode **nodes)
{
	int			i;
	int			u;
	int			v;
	int			*parent;
	
	if (!(parent = init_parent(a->nb_room * 2)))
		exit(-2);
	while (bfs_paths(a, res, parent, nodes))
	{
		i = 0;
		v = a->end;
		while (v != a->start)
		{
			if (v < a->nb_room)
			{
				path->tab[path->size] = push_int(path->tab[path->size], v);
				i++;
			}
			u = parent[v];
			res[u][v] = 1;
			v = u;
		}
		path->tab[path->size] = push_int(path->tab[path->size], v);
		path->path_length[path->size] = i;
		path->size++;
	}
	return (path);
}

void			check_collision(t_path *path, int start, int end)
{
	int			i;
	int			j;
	int			k;
	int			l;

	i = -1;
	while (++i < path->size - 1)
	{
		k = i + 1;
		while (k < path->size)
		{
			j = -1;
			while (++j < path->tab[i]->size)
			{
				l = -1;
				while (++l < path->tab[k]->size)
				{
					if (path->tab[i]->tab[j] == path->tab[k]->tab[l] && path->tab[i]->tab[j] != start && path->tab[i]->tab[j] != end)
						printf("Collision room %d\tpath %d and %d\n", path->tab[i]->tab[j], i, k);
				}
			}
			k++;
		}
	}
}

void			print_false_nodes(t_dynode **nodes, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < nodes[i]->size)
		printf("node[%d]->tab[%d] = %d\n", i, j, nodes[i]->tab[j]);
		printf("---------------\n");
	}
}


t_path			*edmonds_karp(t_anthill *a)
{
	int			**res;
	int			u;
	int			v;
	int			*parent;
	t_path		*path;
	t_dynode	**nodes;

	nodes = create_false_nodes(a);
	print_false_nodes(nodes, a->nb_room * 2);
	u = a->nodes[a->start]->size < a->nodes[a->end]->size ?
		a->nodes[a->start]->size : a->nodes[a->end]->size;
	if (!(path = create_path_tab(u))
		|| !(res = init_matrice(a->nb_room * 2))
		|| !(parent = init_parent(a->nb_room * 2)))
		exit(-2);
	while (bfs(a, res, parent, nodes))
	{
		v = a->end;
		while (v != a->start)
		{
			u = parent[v];
			res[u][v] -= 1;
			res[v][u] += 1;
			v = u;
		}
	}
	// print_matrix(res, a->nb_room*2);
	path = save_paths(a, res, path, nodes);
	check_collision(path, a->start, a->end);
	return (path);
}
