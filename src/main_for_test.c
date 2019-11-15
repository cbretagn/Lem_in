/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/15 13:33:46 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#define SIZE 400

static void		print_tab(char **tab, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (tab[i])
			ft_putendl(tab[i]);
		else
			ft_putendl("(NULL)");
	}
}

#include <stdio.h>

static void		print_dynode(t_dynode **nodes, char **rooms, int size)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		printf("node %d / %s is connected to nodes : ", i, rooms[i]);
		j = -1;
		while (++j < nodes[i]->size)
			printf("%d ", nodes[i]->tab[j]);
		printf("\n");
	}
}

int				main(int argc, char **argv)
{
	t_anthill	*anthill;
	char		*file;
	char		*graph;
	t_data		*data;

	if (!(data = init_struct()) || argc != 2)
		return (0);
	if (!(file = read_file(argv[1])))
		return (0);
	if (!(graph = ft_strsub(file, 0, check_file(file, data))))
		return (0);
	ft_putstr(graph);
	anthill = create_anthill(data->rooms);
	if (anthill)
		write(1, "\nAnthill is here !\n", 19);
	anthill = parser(graph, anthill, data->rooms); //size temporary // size needed ?
	if (anthill)
		write(1, "\nAnthill is still here !\n", 25);
	print_tab(anthill->rooms, data->rooms);
	print_dynode(anthill->nodes, anthill->rooms, anthill->nb_room);
	return (0);
}
