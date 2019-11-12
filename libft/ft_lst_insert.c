/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:28:54 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/22 15:34:57 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_insert(t_list *insert, t_list *previous)
{
	if (!insert || !previous)
		return ;
	insert->next = previous->next;
	previous->next = insert;
}
