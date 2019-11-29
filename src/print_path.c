/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:58:41 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/29 15:19:29 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

#include <stdio.h>

t_ants			print_ants(t_path *path, t_anthill *anthill)
{
	// t_dstring	*buff;

	char		buff[4096];
	int			j;

	int			i;
	int			ant;
	t_ants		*pos_ants;
	int			end;

	if (!(pos_ants = malloc(size_of(t_ants))))
		return (NULL);
	i = 1;
	ant = 0;

	// direct printf version

	while (end < anthill->ants)
	{
			end = 0;
			while (ant < anthill->ants)
			{
				if (i < path->path_length[path->ants[ant]])
					printf("L%d-%s ", ft_itoa(ant+1), anthill->rooms[path->tab[path->ants[ant]]->tab[i]]);
				if (i == path->path_length[path->ants[ant]])
					end++;
				pos_ants->path[ant] = path->ants[ant];
				pos_ants->curr[ant] = i; // or path->tab[path->ants[ant]]->tab[i]
				ant++;
			}
			ft_putchar('\n')
			i++;
	}

	// check if certain that all ants are able to go to the end
	// or find a better way to end the loop

	// dynamic string version
	// shorter if init dyn_s to "\n" and remove "\n" after printing the anthill

	while (end < anthill->ants)
	{
		end = 0;
		while (ant < anthill->ants)
		{
			pos_ants->path[ant] = path->ants[ant];
			pos_ants->curr[ant] = path->tab[path->ants[ant]]->tab[i];
			if (i < path->path_length[path->ants[ant]])
			{
				if (!buff)
				{
					if (!(buff = create_dstring(4096, "L1-")))
						return (NULL);
				}
				else
				{
					if (!(buff = push_str(buff, "L")))
						return (NULL);
					if (!(buff = push_str(buff, ft_itoa(ant + 1))))
						return (NULL);
					if (!(buff = push_str(buff, "-")))
						return (NULL);
				}
				if (!(buff = push_str(buff, anthill->rooms[pos_ants->curr[ant]])))
					return (NULL);
				if (!(buff = push_str(buff, " ")))
					return (NULL);
			}
			if (i == path->path_length[path->ants[ant]])
				end++;
			ant++;
		}
		if (!(buff = push_str(buff, "\n")))
			return (NULL);
		i++;
	}
	ft_putstr(buff->str);

	// buffer version

	j = 0;
	while (end < anthill->ants)
	{
		end = 0;
		while (ant < anthill->ants)
		{
			pos_ants->path[ant] = path->ants[ant];
			pos_ants->curr[ant] = path->tab[path->ants[ant]]->tab[i];
			if (i < path->path_length[path->ants[ant]])
			{
				j += ft_strlen(ft_itoa(ant + 1)) + ft_strlen(anthill->rooms[pos_ants->curr[ant]]) + 3;
				if (j >= 4095)
				{
					buff[ft_strlen(buff)] = '\0';
					ft_putstr(buff->str);
					ft_bzero(buff, ft_strlen(buff));
					j = 0;
				}
				buff[ft_strlen(buff)] = 'L';
				ft_strcat(buff, ft_itoa(ant + 1));
				buff[ft_strlen(buff)] = '-';
				ft_strcat(buff, anthill->rooms[pos_ants->curr[ant]]);
				buff[ft_strlen(buff)] = ' ';
			}
			if (i == path->path_length[path->ants[ant]])
				end++;
			ant++;
		}
		buff[ft_strlen(buff)] = '\n';
		j++;
		i++;
	}
	ft_putstr(buff->str);
}

void     		print_path(char *graph, t_path *path, t_anthill *anthill)
{
	t_ants		*ants;

	ft_putendl(graph);
    if (!(ants = print_ants(path, anthill)))
		exit(-2);
}