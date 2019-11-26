/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_relabel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:38:21 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/26 14:22:41 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

#include <stdio.h>

void		init_preflow(t_anthill *anthill)
{
	int     i;
    int     nb_co;

    i = -1;
    nb_co = 0;
    while (++i < NB_ROOM)
    {
		if (CONNECTORS[i])
			nb_co++;
    }
    CONNECTORS[anthill->start]->height = nb_co;
    i = 0;
    while (i < )
}

