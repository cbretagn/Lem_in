/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:58:41 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/29 17:47:44 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

#include <stdio.h>

static int		check_path(int ant, t_anthill *anthill, t_ants *pos_ants)
{
	int			i;

	i = 0;
	while (i < anthill->ants)
	{
		if (pos_ants->path[ant] == pos_ants->path[i]
			&& pos_ants->next[ant] == pos_ants->curr[i])
			return (0);
		i++;
	}
	return (1);
}

static t_ants	print_ants(t_path *path, t_anthill *anthill)
{
	// t_dstring	*buff;

	// char		buff[4096];
	// int			j;

	int			i;
	int			ant;
	t_ants		*pos_ants;
	int			end;

	if (!(pos_ants = malloc(size_of(t_ants))))
		return (NULL);
	i = 1;
	ant = 0;
	while (ant < anthill->ants)
	{
		pos_ants->curr[ant] = 0;
		ant++;
	}
	ant = 0;
	// direct printf version

	while (end < anthill->ants)
	{
			end = 0;
			while (ant < anthill->ants)
			{
				pos_ants->path[ant] = path->ants[ant];
				pos_ants->next[ant] = pos_ants->curr[ant] + 1;
				if (i < path->path_length[path->ants[ant]] && check_path(ant, anthill, pos_ants))
				{
					printf("L%d-%s ", ft_itoa(ant + 1), anthill->rooms[pos_ants->curr[ant]]);
					pos_ants->curr[ant] += 1;
				}
				if (pos_ants->curr[ant] == path->path_length[path->ants[ant]])
					end++;
				ant++;
			}
			ft_putchar('\n')
			i++;
	}

	// check if certain that all ants are able to go to the end
	// or find a better way to end the loop

	// dynamic string version

	// if (!(buff = create_dstring(4096, "")))
	// 	return (NULL);
	// while (end < anthill->ants)
	// {
	// 	end = 0;
	// 	while (ant < anthill->ants)
	// 	{
	// 		pos_ants->path[ant] = path->ants[ant];
	// 		pos_ants->next[ant] = pos_ants->curr[ant] + 1;
	// 		if (i < path->path_length[path->ants[ant]] && check_path(ant, anthill, pos_ants))
	// 		{
	// 			if (!(buff = push_str(buff, "L")))
	// 				return (NULL);
	// 			if (!(buff = push_str(buff, ft_itoa(ant + 1))))
	// 				return (NULL);
	// 			if (!(buff = push_str(buff, "-")))
	// 				return (NULL);
	// 			if (!(buff = push_str(buff, anthill->rooms[pos_ants->curr[ant]])))
	// 				return (NULL);
	// 			if (!(buff = push_str(buff, " ")))
	// 				return (NULL);
	// 			pos_ants->curr[ant] += 1;
	// 		}
	// 		if (pos_ants->curr[ant] == path->path_length[path->ants[ant]])
	// 			end++;
	// 		ant++;
	// 	}
	// 	if (!(buff = push_str(buff, "\n")))
	// 		return (NULL);
	// 	i++;
	// }
	// ft_putstr(buff->str);

	// buffer version

	// j = 0;
	// while (end < anthill->ants)
	// {
	// 	end = 0;
	// 	while (ant < anthill->ants)
	// 	{
	// 		pos_ants->path[ant] = path->ants[ant];
	// 		pos_ants->curr[ant] = path->tab[path->ants[ant]]->tab[i];
	// 		if (i < path->path_length[path->ants[ant]] && check_path(ant, anthill, pos_ants))
	// 		{
	// 			j += ft_strlen(ft_itoa(ant + 1)) + ft_strlen(anthill->rooms[pos_ants->curr[ant]]) + 3;
	// 			if (j >= 4095)
	// 			{
	// 				buff[ft_strlen(buff)] = '\0';
	// 				ft_putstr(buff->str);
	// 				ft_bzero(buff, ft_strlen(buff));
	// 				j = 0;
	// 			}
	// 			buff[ft_strlen(buff)] = 'L';
	// 			ft_strcat(buff, ft_itoa(ant + 1));
	// 			buff[ft_strlen(buff)] = '-';
	// 			ft_strcat(buff, anthill->rooms[pos_ants->curr[ant]]);
	// 			buff[ft_strlen(buff)] = ' ';
	// 			pos_ants->curr[ant] += 1;
	// 		}
	// 		if (pos_ants->curr[ant] == path->path_length[path->ants[ant]])
	// 			end++;
	// 		ant++;
	// 	}
	// 	buff[ft_strlen(buff)] = '\n';
	// 	j++;
	// 	i++;
	// }
	// ft_putstr(buff->str);
}

void     		print_path(char *graph, t_path *path, t_anthill *anthill)
{
	t_ants		*ants;

	ft_putendl(graph);
    if (!(ants = print_ants(path, anthill)))
		exit(-2);
}