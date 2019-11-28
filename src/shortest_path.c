/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:51:10 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/28 14:50:39 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int     init_queue(t_file *queue, int start)
{
    if (!(queue = malloc(sizeof(t_file)))
        return (0);
    queue->v = start;
    queue->next = NULL;
    return (1);
}

int     

int		shortest_path(t_anthill *anthill)
{
    t_file  *queue;

    if (!(queue = init_queue(queue, anthill->start)))
        return (0);


}
