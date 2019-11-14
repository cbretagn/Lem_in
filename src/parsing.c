/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:20:29 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/14 16:06:30 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

//receives char *, hash room, check if repetition
//creates adjency list

static int			next_line(char *str, int i)
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

t_anthill			*parser(char *str, t_anthill *anthill, int size) // and adjency list /matrix i dunno
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
		if (!(anthill->rooms = put_in_table(word->str, anthill->rooms, size)))
			return (NULL); //free anthill
		word->size = 0;
	}
	return (anthill);
	//handle tubes
}
