/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:37:05 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/12 15:43:10 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	free_path(t_path *routes)
{
	int	i;

	i = -1;
	free(routes->path_length);
	routes->path_length = NULL;
	free(routes->nb_ants);
	routes->nb_ants = NULL;
	while (++i < routes->size)
		delete_dynode(routes->tab[i]);
	routes->tab = NULL;
	routes = NULL;
}
