/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:20:29 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/12 14:07:52 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

//receives char *, hash room, check if repetition
//creates adjency list

int				next_line(char *str, int i)
{
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\0')
		return (i);
	return (i + 1);
}

//dynamic string to hold the word
//reset size to 0 to write new
//use push_str_nchar with size of room name

t_anthill		*handle_tubes(t_anthill *anthill, char *str, int i,
					t_dstring *word)
{
	int			j;
	int			node;
	int			connecting;

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
		NODES[node] = push_int(NODES[node], connecting);
		NODES[connecting] = push_int(NODES[connecting], node);
		word->size = 0;
		i = next_line(str, i);
	}
	delete_dstring(word);
	return (anthill);
}



// t_anthill		*handle_tubes(t_anthill *anthill, char *str, int i,
// 					t_dstring *word)
// {
// 	int			j;
// 	int			node;
// 	int			connecting;

// 	j = -1;
// 	while (++j < NB_ROOM)
// 	{
// 		if (j == anthill->end || j == anthill->start)
// 			continue ;
// 		NODES[j] = push_int(NODES[j], j + NB_ROOM);
// 		NODES[j + NB_ROOM] = push_int(NODES[j + NB_ROOM], j);
// 	}
// 	while (str[i])
// 	{
// 		while (str[i] == '#')
// 			i = next_line(str, i);
// 		if (!str[i])
// 			break ;
// 		j = i;
// 		while (str[j] != '-')
// 			j++;
// 		word = push_str_nchar(word, str + i, j - i);
// 		node = search_in_table(word->str, ROOMS, NB_ROOM);
// 		j++;
// 		i = j;
// 		while (str[j] != '\n' && str[j])
// 			j++;
// 		word->size = 0;
// 		word = push_str_nchar(word, str + i, j - i);
// 		connecting = search_in_table(word->str, ROOMS, NB_ROOM);
// 		if (node == anthill->start || connecting == anthill->start)
// 			{NODES[node] = push_int(NODES[node], connecting);
// 			NODES[connecting] = push_int(NODES[connecting], node);}
// 		else if (connecting == anthill->end)
// 			{NODES[node + NB_ROOM] = push_int(NODES[node + NB_ROOM], connecting);
// 			NODES[connecting] = push_int(NODES[connecting], node + NB_ROOM);}
// 		else if (node == anthill->end)
// 			{NODES[node] = push_int(NODES[node], connecting + NB_ROOM);
// 			NODES[connecting + NB_ROOM] = push_int(NODES[connecting + NB_ROOM], node);}
// 		else
// 			{NODES[node + NB_ROOM] = push_int(NODES[node + NB_ROOM], connecting);
// 			NODES[connecting] = push_int(NODES[connecting + NB_ROOM], node);}
// 		word->size = 0;
// 		i = next_line(str, i);
// 	}
// 	delete_dstring(word);
// 	return (anthill);
// }

t_anthill		*parser(char *str, t_anthill *anthill, t_data *data)
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
		// printf("str = %.6s j-i = %d\n", str + i, j - i);
		// printf("word is %s\n", word->str);
		if (!(ROOMS = put_in_table(word->str, ROOMS, data->rooms)))
			return (NULL); //free anthill
	}
	anthill->start = search_in_table(data->start_room, ROOMS, NB_ROOM);
	anthill->end = search_in_table(data->end_room, ROOMS, NB_ROOM);
	anthill = handle_tubes(anthill, str, i, word);
	anthill->ants = data->ants;
	return (anthill);
}
