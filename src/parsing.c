/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:20:29 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 17:19:49 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int				next_line(char *str, int i)
{
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\0')
		return (i);
	return (i + 1);
}

static void		fill_anthill_int(t_anthill *anthill, t_data *data)
{
	anthill->start = search_in_table(data->start_room,
		anthill->rooms, anthill->nb_room);
	anthill->end = search_in_table(data->end_room, anthill->rooms,
		anthill->nb_room);
	anthill->ants = data->ants;
}

t_anthill		*parser(char *str, t_anthill *anth, t_data *data)
{
	int			i;
	int			j;
	t_dstring	*word;

	i = 0;
	if (!(word = create_dstring(5, "")))
		return (NULL);
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
		if (!(anth->rooms = put_in_table(word->str, anth->rooms, data->rooms)))
			return (NULL);
	}
	anth = handle_tubes(anth, str, i, word);
	fill_anthill_int(anth, data);
	return (anth);
}
