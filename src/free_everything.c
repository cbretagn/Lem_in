/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:37:05 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/12 18:33:05 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		free_path(t_path *routes)
{
	int	i;

	i = -1;
	if (!routes)
		return ;
	free(routes->path_length);
	routes->path_length = NULL;
	free(routes->nb_ants);
	routes->nb_ants = NULL;
	while (++i < routes->cap)
		delete_dynode(routes->tab[i]);
	free(routes->tab);
	routes->tab = NULL;
	free(routes);
	routes = NULL;
}

int			ret_free_line(char *str)
{
	ft_strdel(&str);
	return (0);
}

void		free_matrice(int **mat, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat);
	mat = NULL;
}

int			ret_free_q(int ret, t_pile *q)
{
	if (q)
		del_pile(q);
	return (ret);
}

void		exit_malloc(int error)
{
	write(2, "Malloc error, sorry :'(\n", 24);
	exit(error);
}
