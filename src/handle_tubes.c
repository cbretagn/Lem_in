/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tubes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:13:06 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/10 17:27:13 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		init_inter_nodes(t_anthill *anthill)
{
	int			i;

	i = -1;
	while (++i < anthill->nb_room)
	{
		anthill->inter_nodes[i] = push_int(anthill->inter_nodes[i],
			i + anthill->nb_room);
		anthill->inter_nodes[i + anthill->nb_room] =
			push_int(anthill->inter_nodes[i + anthill->nb_room], i);
	}
}

static void		fill_nodes(t_anthill *anthill, int node, int connecting)
{
	anthill->nodes[node] = push_int(anthill->nodes[node], connecting);
	anthill->nodes[connecting] = push_int(anthill->nodes[connecting], node);
	anthill->inter_nodes[node] = push_int(anthill->inter_nodes[node],
		connecting + anthill->nb_room);
	anthill->inter_nodes[connecting] =
		push_int(anthill->inter_nodes[connecting], node + anthill->nb_room);
	anthill->inter_nodes[node + anthill->nb_room] =
		push_int(anthill->inter_nodes[node + anthill->nb_room], connecting);
	anthill->inter_nodes[connecting + anthill->nb_room] =
		push_int(anthill->inter_nodes[connecting + anthill->nb_room], node);
}

t_anthill		*handle_tubes(t_anthill *anthill, char *str, int i,
					t_dstring *word)
{
	int			j;
	int			node;
	int			connecting;

	init_inter_nodes(anthill);
	while (str[i])
	{
		while (str[i] == '#')
			i = next_line(str, i);
		if (!str[i])
			break ;
		j = i;
		while (str[j] != '-')
			j++;
		word = push_str_nchar(word, str + i, j - i);
		node = search_in_table(word->str, anthill->rooms, anthill->nb_room);
		j++;
		i = j;
		while (str[j] != '\n' && str[j])
			j++;
		word->size = 0;
		word = push_str_nchar(word, str + i, j - i);
		connecting = search_in_table(word->str, anthill->rooms, anthill->nb_room);
		fill_nodes(anthill, node, connecting);
		word->size = 0;
		i = next_line(str, i);
	}
	delete_dstring(word);
	return (anthill);
}
