/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/14 18:36:14 by cbretagn         ###   ########.fr       */
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
	char		*str;

	anthill = create_anthill(2592);
	if (argc == 2)
	{
		str = read_file(argv[1]);
		anthill = parser(str, anthill, 2592); //size temporary
	}
	print_tab(anthill->rooms, 2592);
	print_dynode(anthill->nodes, anthill->rooms, anthill->nb_room);
	return (0);
}
