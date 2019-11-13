/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:16:15 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/17 17:55:06 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sep(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
		return (1);
	if (c == '\v' || c == '\f')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	long	nbr;
	int		neg;

	neg = 1;
	nbr = 0;
	while (*str && ft_sep(*str))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	nbr = nbr * neg;
	return (int)nbr;
}
