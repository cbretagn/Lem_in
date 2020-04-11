/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_path_ek.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:23:46 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/12 17:27:58 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		update_paths(t_path *path, int v, int i)
{
	path->tab[path->size] = push_int(path->tab[path->size], v);
	path->path_length[path->size] = i;
	path->size++;
}

t_path		*reverse_paths(t_path *path)
{
	t_path	*rpath;
	int		i;
	int		j;

	if (!(rpath = create_path_tab(path->size)))
		exit(-2);
	rpath->size = path->size;
	i = -1;
	while (++i < path->size)
	{
		rpath->path_length[i] = path->path_length[i];
		j = path->path_length[i] + 1;
		while (j--)
			rpath->tab[i] = push_int(rpath->tab[i], path->tab[i]->tab[j]);
	}
	free_path(path);
	return (rpath);
}

void		update_residual_graph(int v, t_anthill *a, int **res)
{
	int		j;

	j = -1;
	if (v != a->start)
	{
		while (++j < a->nb_room)
			res[v][j] = 1;
	}
}

int			proceed(int v, t_anthill *a, t_pile *queue)
{
	if (v != a->end)
		add_to_top(queue, v);
	else
		return (0);
	return (1);
}
