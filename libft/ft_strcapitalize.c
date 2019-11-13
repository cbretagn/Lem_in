/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:49:33 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/22 17:19:06 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issep(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

char		*ft_strcapitalize(char *s, char *sep)
{
	char	*temp;

	temp = s;
	while (*temp)
	{
		if (ft_isupper(*temp))
			*temp = *temp + 32;
		temp++;
	}
	temp = s;
	if (ft_islower(*temp))
		*temp = *temp - 32;
	temp++;
	while (*temp)
	{
		if (ft_islower(*temp) && ft_issep(*(temp - 1), sep))
			*temp = *temp - 32;
		temp++;
	}
	return (s);
}
