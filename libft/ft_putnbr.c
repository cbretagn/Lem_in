/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:45:17 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/16 19:12:16 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long hold;

	hold = n;
	if (n < 0)
	{
		ft_putchar('-');
		hold = hold * -1;
	}
	if (hold < 10)
		ft_putchar(hold + '0');
	if (hold > 9)
	{
		ft_putnbr(hold / 10);
		ft_putchar(hold % 10 + '0');
	}
}
