/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:40:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/06 18:47:50 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>

int			main(int argc, char **argv)
{
	(void)argc;

	char c;
	int i = -1;
	int hash = 456;
	while ((c = argv[1][++i]))
	{
		hash = hash * 31 + c;
	}
	hash = hash;
	printf("%d\n", hash);
}
