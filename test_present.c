/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_present.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:19:35 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/06 18:49:17 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include "./get_next_line.h"
#include <stdio.h>

void		check_present(int check, int tab[10000])
{
	int res;

	res = 0;
	int i = -1;
	while (++i < 10000)
	{
		if (tab[i] == check)
		{
			tab[i] = -1;
			res++;
		}
	}
	if (res > 1)
		printf("%d is present %d times\n", check, res);
}

void		init_tab(int tab[1000])
{
	int i = -1;
	while (++i < 10000)
	{
		tab[i] = -1;
	}
}

int			main(void)
{
	char 	*str;
	int		tab[10000];

	int		i = 0;
	init_tab(tab);
	while (get_next_line(0, &str))
	{
		tab[i] = ft_atoi(str);
		ft_strdel(&str);
		i++;
	}
	i = -1;
	while (++i < 10000)
	{
		if (tab[i] != -1)
			check_present(tab[i], tab);
	}
}
