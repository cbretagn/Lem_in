/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:20:29 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/19 15:23:29 by sadahan          ###   ########.fr       */
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

static int		in_array(t_dynode *dynode, int node)
{
	int			i;

	i = 0;
	while (i < dynode->size)
	{
		if (dynode->tab[i] == node)
			return (1);
		i++;
	}
	return (0);
}

//dynamic string to hold the word
//reset size to 0 to write new
//use push_str_nchar with size of room name

t_anthill		*handle_tubes(t_anthill *anthill, char *str, int i,
				t_dstring *word)
{
	int			j;
	int			node;
	int			connect;

	// write(1, str + i, 10);
	// ft_putnbr(ft_strlen(str));
	// ft_putchar('\n');
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
		connect = search_in_table(word->str, anthill->rooms, anthill->nb_room);
		// check in nodes[node] if connect exists
		if (!(in_array(anthill->nodes[node], connect)))
			anthill->nodes[node] = push_int(anthill->nodes[node], connect);
		if (!(in_array(anthill->nodes[connect], node)))
			anthill->nodes[connect] = push_int(anthill->nodes[connect], node);
		word->size = 0;
		i = next_line(str, i);
	}
	delete_dstring(word);
	return (anthill);
}

t_anthill		*parser(char *str, t_anthill *anthill) // and adjency list /matrix i dunno
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
		if (!(anthill->rooms = put_in_table(word->str, anthill->rooms,
			anthill->nb_room)))
			return (NULL); //free anthill
		word->size = 0;
	}
	anthill = handle_tubes(anthill, str, i, word);
	return (anthill);
}
