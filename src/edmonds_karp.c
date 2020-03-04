/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:13:09 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/04 16:37:10 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		bfs(t_anthill *a, int **res, int *parent, int **cap)
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
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
			if (cap[u][v] - res[u][v] > 0 && parent[v] == -1)
			{
				parent[v] = u;
				if (v != a->end)
				{
					if (queue)
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

static int		bfs_paths(t_anthill *a, int **res, int *parent)
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
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
			if (res[u][v] >= 1 && parent[v] == -1)
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

static t_path	*save_paths(t_anthill *a, int **res, t_path *path)
{
	int			i;
	int			u;
	int			v;
	int			*parent;

	if (!(parent = init_parent(a->nb_room * 2)))
		exit(-2);
	while (bfs_paths(a, res, parent))
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
			res[u][v] -= 1;
			v = u;
		}
		path->tab[path->size] = push_int(path->tab[path->size], v);
		path->path_length[path->size] = i;
		path->size++;
	}
	return (path);
}

static void			run_bfs(t_anthill *a, int **res, int *parent, int u, int **cap)
{
	int v;
	
	while (bfs(a, res, parent, cap))
	{
		v = a->end;
		while (v != a->start)
		{
			u = parent[v];
			res[u][v] += 1;
			res[v][u] -= 1;
			v = u;
		}
	}
}

t_path			*edmonds_karp1(t_anthill *a)
{
	int			**res;
	int			u;
	int			*parent;
	int			**cap;
	t_path		*path;

	u = a->nodes[a->start]->size < a->nodes[a->end]->size ?
		a->nodes[a->start]->size : a->nodes[a->end]->size;
	if (!(path = create_path_tab(u))
		|| !(res = init_matrice(a->nb_room * 2, 0))
		|| !(cap = init_mat_capacity(a))
		|| !(parent = init_parent(a->nb_room * 2)))
		exit(-2);
	run_bfs(a, res, parent, u, cap);
	path = save_paths(a, res, path);
	return (path);
}
