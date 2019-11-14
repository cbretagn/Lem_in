/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/14 16:06:55 by cbretagn         ###   ########.fr       */
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

static void		init_tab(char **tab, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		tab[i] = NULL;
}

int				main(int argc, char **argv)
{
	t_anthill	*anthill;
	char		*str;

	if (!(anthill = (t_anthill *)malloc(sizeof(t_anthill))))
		return (-1);
	if (!(anthill->rooms = (char **)malloc(sizeof(char *) * 2592)))
		return (-1);
	init_tab(anthill->rooms, 2592);
	if (argc == 2)
	{
		str = read_file(argv[1]);
		anthill = parser(str, anthill, 2592); //size temporary
	}
	print_tab(anthill->rooms, 2592);
	return (0);
}
