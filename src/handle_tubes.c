/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tubes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <cbretagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:13:06 by sadahan           #+#    #+#             */
/*   Updated: 2020/04/27 18:06:32 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static t_anthill	*free_return(t_anthill *anthill, t_dstring *word, int i)
{
	delete_dstring(word);
	if (i == 1)
	{
		delete_anthill(anthill, -1);
		return (NULL);
	}
	return (anthill);
}

static void			init_inter_nodes(t_anthill *anthill)
{
	int				i;

	i = -1;
	while (++i < anthill->nb_room)
	{
		anthill->inter_nodes[i] = push_int(anthill->inter_nodes[i],
			i + anthill->nb_room);
		anthill->inter_nodes[i + anthill->nb_room] =
			push_int(anthill->inter_nodes[i + anthill->nb_room], i);
	}
}

static void			fill_nodes(t_anthill *anthill, int node, int connecting)
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

static int			define_node(t_anthill *anthill, t_dstring *word,
						char *str, int n)
{
	int				node;

	word->size = 0;
	word = push_str_nchar(word, str, n);
	node = search_in_table(word->str, anthill->rooms, anthill->nb_room);
	return (node);
}

t_anthill			*handle_tubes(t_anthill *anthill, char *str, int i,
						t_dstring *word)
{
	int				j;
	int				node;
	int				connecting;

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
		node = define_node(anthill, word, str + i, j - i);
		i = ++j;
		while (str[j] != '\n' && str[j])
			j++;
		connecting = define_node(anthill, word, str + i, j - i);
		if (node == -1 || connecting == -1)
			return (free_return(anthill, word, 1));
		fill_nodes(anthill, node, connecting);
		i = next_line(str, i);
	}
	return (free_return(anthill, word, 0));
}
