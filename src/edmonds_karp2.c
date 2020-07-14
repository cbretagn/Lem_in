/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:17:20 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:36 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		bfs_ek2(t_anthill *a, int **res, int *parent)
{
	t_pile		*queue;
	int			u;
	int			v;
	int			i;

	if (!(queue = init_pile(a->start)))
		exit(-2);
	reset_parent(parent, a->nb_room, a);
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
			if (res[u][v] > 0 && parent[v] == -1)
			{
				parent[v] = u;
				if (!(proceed(v, a, queue)))
					return (ret_free_q(1, queue));
			}
		}
	}
	return (ret_free_q(0, queue));
}

static int		bfs_paths2(t_anthill *a, int **res, int *parent)
{
	t_pile		*queue;
	int			u;
	int			v;
	int			i;

	if (!(queue = init_pile(a->start)))
		exit(-2);
	reset_parent(parent, a->nb_room, a);
	while (queue->nb_elem > 0)
	{
		i = -1;
		u = del_bottom(queue);
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
			if (res[u][v] == 0 && parent[v] == -1)
			{
				parent[v] = u;
				if (!(proceed(v, a, queue)))
					return (ret_free_q(1, queue));
			}
		}
	}
	return (ret_free_q(0, queue));
}

static t_path	*save_paths2(t_anthill *a, int **res, t_path *path,
					int i)
{
	int			u;
	int			v;
	int			*parent;

	if (!(parent = init_parent(a->nb_room)))
		exit(-2);
	while (bfs_paths2(a, res, parent))
	{
		i = 0;
		v = a->end;
		while (v != a->start)
		{
			if (v < a->nb_room)
				path->tab[path->size] = push_int(path->tab[path->size], v);
			i = v < a->nb_room ? i + 1 : i;
			u = parent[v];
			res[u][v] = 1;
			v = u;
			update_residual_graph(v, a, res);
		}
		update_paths(path, v, i);
	}
	free(parent);
	parent = NULL;
	return (path);
}

static void		run_bfs2(t_anthill *a, int **res, int *parent)
{
	int			u;
	int			v;

	while (bfs_ek2(a, res, parent))
	{
		v = a->end;
		while (v != a->start)
		{
			u = parent[v];
			res[u][v] = 0;
			res[v][u] = 1;
			v = u;
		}
	}
}

t_path			*edmonds_karp2(t_anthill *a)
{
	int			**res;
	int			nb_path;
	int			*parent;
	t_path		*path;

	nb_path = a->nodes[a->start]->size < a->nodes[a->end]->size ?
		a->nodes[a->start]->size : a->nodes[a->end]->size;
	if (!(path = create_path_tab(nb_path))
		|| !(res = init_matrice(a->nb_room, 1))
		|| !(parent = init_parent(a->nb_room)))
		exit(-2);
	run_bfs2(a, res, parent);
	free(parent);
	parent = NULL;
	path = save_paths2(a, res, path, 0);
	path = reverse_paths(path);
	free_matrice(res, a->nb_room);
	return (path);
}
