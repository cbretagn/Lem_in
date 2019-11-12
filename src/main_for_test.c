/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:28:48 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/12 14:49:14 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
#define SIZE 400

static void		print_tab(char **tab, int size)
{
	int		i;

	i = -1;
	while (++i < SIZE)
		ft_putendl(tab[i]);
}

int				main(int argc, char **argv)
{
	char	**tab;
	char	*str;

	if (!(tab = (char **)malloc(sizeof(char *) * SIZE)))
		return (-1);
	while (get_next_line(0, &str) > 0)
	{
		tab = put_in_table(str, tab, SIZE);
		ft_strdel(&str);
	}
	print_tab(tab, SIZE);
	ft_putendl(tab[152]);
	ft_putendl(tab[search_in_table(tab[152], tab, SIZE)]);
	return (0);
}
