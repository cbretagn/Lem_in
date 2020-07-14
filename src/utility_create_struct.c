/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_create_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:53:42 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 19:05:29 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_dynode		**create_node_tab(int size)
{
	t_dynode	**ret;
	int			i;

	i = -1;
	if (!(ret = (t_dynode **)malloc(sizeof(t_dynode *) * size)))
		exit(-2);
	while (++i < size)
		ret[i] = create_dynode(BASE_DYN_NODES);
	return (ret);
}
