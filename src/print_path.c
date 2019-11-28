/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:58:41 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/28 16:45:35 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

#include <stdio.h>

// void			print_graph(char *graph, t_dstring *clean_graph)
// {
// 	char		*buff;
// 	int			i;
// 	char		*cmd;

// 	i = 0;
// 	while (graph[i])
// 	{
// 		while (graph[i] != '#')
// 			i++;
// 		if (graph[i] == '#')
// 		{
// 			if (!ft_strncmp(&graph[i], "##start\n", 8) && !(ft_strncmp(&graph[i], "##end\n", 6)))
// 			{
// 				i += 2;
// 				continue ;
// 			}
// 			else
// 			{
// 				if (!clean_graph)
// 				{
// 					if (!(clean_graph = create_dstring(4096, ft_strsub(graph, 0, i))))
// 						return ;
// 				}
// 				else if (!(clean_graph = push_str_nchar(clean_graph, graph, i)))
// 					return ;	
// 			}
// 		}
// 	}
// 	if (clean_graph)
// 		ft_putstr(clean_graph);
// 	else
// 		ft_putstr(graph);
// }

t_ants		print_ants(t_path *path, t_anthill *anthill)
{
	// char	buff[4096];
	int		i;
	int		ant;
	t_ants	*pos_ants;
	int		end;

	if (!(pos_ants = malloc(size_of(t_ants))))
		return (NULL);
	i = 1;
	ant = 1;
	while (end < anthill->ants)
	{
		end = 0;
		while (ant <= anthill->ants)
		{
			if (i < path->path_length[path->ants[ant]])
				printf("L%d-%s ", ft_itoa(ant), anthill->rooms[path->tab[path->ants[ant]][i]]);
			if (i == path->path_length[path->ants[ant]])
				end++;
			ant++;
		}
		ft_putchar('\n')
		i++;
	}

}

void     	print_path(char *graph, t_path *path, t_anthill *anthill)
{
	// t_dstring	*clean_graph;
	t_ants	*ants;

	// clean_graph = NULL;
    // print_graph(graph, clean_graph);
	printf("%s\n", graph);
    ants = print_ants(path, anthill);
}