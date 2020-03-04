/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:20:29 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/04 15:53:32 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

//receives char *, hash room, check if repetition
//creates adjency list


//dynamic string to hold the word
//reset size to 0 to write new
//use push_str_nchar with size of room name


static t_anthill		*handle_tubes(t_anthill *anthill, char *str, int i,
					t_dstring *word)
{
	int			j;
	int			node;
	int			connecting;

	j = -1;
	while (++j < NB_ROOM)
	{
		// if (j == anthill->start || j == anthill->end)
		// 	continue ;
		NODES[j] = push_int(NODES[j], j + NB_ROOM);
		NODES[j + NB_ROOM] = push_int(NODES[j + NB_ROOM], j);
		anthill->nodes2[j] = push_int(anthill->nodes2[j], j + NB_ROOM);
		// anthill->nodes2[j + NB_ROOM] = push_int(anthill->nodes2[j + NB_ROOM], j);
	}
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
		node = search_in_table(word->str, ROOMS, NB_ROOM);
		j++;
		i = j;
		while (str[j] != '\n' && str[j])
			j++;
		word->size = 0;
		word = push_str_nchar(word, str + i, j - i);
		connecting = search_in_table(word->str, ROOMS, NB_ROOM);
		anthill->nodes2[node + NB_ROOM] = push_int(anthill->nodes2[node + NB_ROOM], connecting);
		anthill->nodes2[connecting + NB_ROOM] = push_int(anthill->nodes2[connecting + NB_ROOM], node);
		NODES[node] = push_int(NODES[node], connecting + NB_ROOM);
		NODES[connecting] = push_int(NODES[connecting], node + NB_ROOM);
		NODES[node + NB_ROOM] = push_int(NODES[node + NB_ROOM], connecting);
		NODES[connecting + NB_ROOM] = push_int(NODES[connecting + NB_ROOM], node);
		word->size = 0;
		i = next_line(str, i);
	}
	delete_dstring(word);
	return (anthill);
}

t_anthill		*parser2(char *str, t_anthill *anthill, t_data *data)
{
	int			i;
	int			j;
	t_dstring	*word;

	i = 0;
	if (!(word = create_dstring(5, "")))
		return (NULL); //free anthill
	while (str[i])
	{
		i = next_line(str, i);
		while (str[i] == '#')
			i = next_line(str, i);
		j = i;
		while (str[j] != ' ' && str[j] != '\n' && str[j])
			j++;
		if (str[j] == '\n')
			break ;
		word = push_str_nchar(word, str + i, j - i);
		word->size = 0;
		if (!(ROOMS = put_in_table(word->str, ROOMS, data->rooms)))
			return (NULL); //free anthill
	}
	anthill->start = search_in_table(data->start_room, ROOMS, NB_ROOM);
	anthill->end = search_in_table(data->end_room, ROOMS, NB_ROOM);
	anthill = handle_tubes(anthill, str, i, word);
	anthill->ants = data->ants;
	return (anthill);
}
