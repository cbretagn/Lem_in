/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:45:17 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/16 19:28:09 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long hold;

	hold = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		hold = hold * -1;
	}
	if (hold < 10)
		ft_putchar_fd(hold + '0', fd);
	if (hold > 9)
	{
		ft_putnbr_fd(hold / 10, fd);
		ft_putchar_fd(hold % 10 + '0', fd);
	}
}
