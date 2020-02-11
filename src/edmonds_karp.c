/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:13:09 by sadahan           #+#    #+#             */
/*   Updated: 2020/02/07 12:53:54 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		bfs(t_anthill *a, int **res, int *parent, int mode)
{
	t_pile		*queue;
	int			u;
	int			v;
	int			i;

	if (!(queue = init_pile(a->start)))
		exit(-2);
	i = -1;
	while (++i < a->nb_room)
		parent[i] = -1;
	parent[a->start] = -2;
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
			if (mode == 1 && res[u][v] > 0 && parent[v] == -1)
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
			else if (mode == 0 && res[u][v] == 0 && parent[v] == -1)
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

static t_path	*save_paths(t_anthill *a, int **res, t_path *path)
{
	int			i;
	int			u;
	int			v;
	int			*parent;

	if (!(parent = init_parent(a)))
		exit(-2);
	while (bfs(a, res, parent, 0))
	{
		i = 0;
		v = a->end;
		while (v != a->start)
		{
			path->tab[path->size] = push_int(path->tab[path->size], v);
			u = parent[v];
			res[u][v] = 1;
			v = u;
			i++;
		}
		path->tab[path->size] = push_int(path->tab[path->size], v);
		path->path_length[path->size] = i;
		path->size++;
	}
	return (path);
}

void			check_collision(int **res, int size)
{
	int i = -1;
	int j;
	int count;

	while (++i < size)
	{
		count = 0;
		j = -1;
		while (++j < size)
		{
			if (res[i][j] == 0)
				count++;
		}
		if (count > 1)
			printf("Collision room %d !\n", i);
	}
	// i = -1;
	// while (++i < size)
	// {
	// 	count = 0;
	// 	j= -1;
	// 	while (++j < size)
	// 	{
	// 		if (res[j][i] == 0)
	// 			count++;
	// 	}
	// 	if (count > 1)
	// 		printf("Collision room %d !\n", i);
	// }
}

t_path			*edmonds_karp(t_anthill *a)
{
	int			**res;
	int			u;
	int			v;
	int			*parent;
	t_path		*path;

	u = a->nodes[a->start]->size < a->nodes[a->end]->size ?
		a->nodes[a->start]->size : a->nodes[a->end]->size;
	if (!(path = create_path_tab(u))
		|| !(res = init_matrice(a))
		|| !(parent = init_parent(a)))
		exit(-2);
	while (bfs(a, res, parent, 1))
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
	check_collision(res, a->nb_room);
	path = save_paths(a, res, path);
	return (path);
}
