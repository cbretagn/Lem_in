/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmonds_karp2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:17:20 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/04 16:27:41 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int		bfs(t_anthill *a, int **res, int *parent)
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
		// printf("---------\nu = %d\n", u);
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
			// printf("v = %d\n", v);
			if (res[u][v] > 0 && parent[v] == -1)
			{
				parent[v] = u;
				if (v != a->end)
				{
					// printf("queued\n");
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


static int		bfs_paths(t_anthill *a, int **res, int *parent)
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
				// printf("---------\nu = %d\n", u);
		while (++i < a->nodes[u]->size)
		{
			v = a->nodes[u]->tab[i];
				// printf("v = %d\tp[v] = %d\tres[uv] = %d\n", v, parent[v], res[u][v]);
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

static t_path	*save_paths(t_anthill *a, int **res, t_path *path)
{
	int			i;
	int			u;
	int			v;
	int			*parent;
	int j;

	if (!(parent = init_parent(a->nb_room)))
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
			res[u][v] = 1;
			v = u;
			j = -1;
			if (v != a->start)
			{
				while (++j < a->nb_room)
					res[v][j] = 1;
			}
		}
		path->tab[path->size] = push_int(path->tab[path->size], v);
		path->path_length[path->size] = i;
		path->size++;
	}
	return (path);
}

static void			run_bfs(t_anthill *a, int **res, int *parent, int u)
{
	int v;
	
	while (bfs(a, res, parent))
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
	int			u;
	int			*parent;
	t_path		*path;

	u = a->nodes[a->start]->size < a->nodes[a->end]->size ?
		a->nodes[a->start]->size : a->nodes[a->end]->size;
	if (!(path = create_path_tab(u))
		|| !(res = init_matrice(a->nb_room, 1))
		|| !(parent = init_parent(a->nb_room)))
		exit(-2);
	run_bfs(a, res, parent, u);
	path = save_paths(a, res, path);
	return (path);
}
