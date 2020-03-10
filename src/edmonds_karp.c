/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:13:09 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/10 13:57:19 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		bfs_ek1(t_anthill *a, int **res, int *parent, int **cap)
{
	t_pile		*queue;
	int			u;
	int			v;
	int			i;

	if (!(queue = init_pile(a->start)))
		exit(-2);
	reset_parent(parent, a->nb_room * 2, a);
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		while (++i < a->inter_nodes[u]->size)
		{
			v = a->inter_nodes[u]->tab[i];
			if (cap[u][v] - res[u][v] > 0 && parent[v] == -1)
			{
				parent[v] = u;
				if (!(queue = proceed(v, a, queue)))
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
	reset_parent(parent, a->nb_room * 2, a);
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		while (++i < a->inter_nodes[u]->size)
		{
			v = a->inter_nodes[u]->tab[i];
			if (res[u][v] >= 1 && parent[v] == -1)
			{
				parent[v] = u;
				if (!(queue = proceed(v, a, queue)))
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
		update_paths(path, v, i);
	}
	return (path);
}

static void		run_bfs1(t_anthill *a, int **res, int *parent, int **cap)
{
	int			u;
	int			v;

	u = 0;
	while (bfs_ek1(a, res, parent, cap))
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
	int			nb_path;
	int			*parent;
	int			**cap;
	t_path		*path;

	nb_path = a->nodes[a->start]->size < a->nodes[a->end]->size ?
		a->nodes[a->start]->size : a->nodes[a->end]->size;
	if (!(path = create_path_tab(nb_path))
		|| !(res = init_matrice(a->nb_room * 2, 0))
		|| !(cap = init_mat_capacity(a))
		|| !(parent = init_parent(a->nb_room * 2)))
		exit(-2);
	run_bfs1(a, res, parent, cap);
	path = save_paths(a, res, path);
	path = reverse_paths(path);
	return (path);
}
