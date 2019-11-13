/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:14:43 by cbretagn          #+#    #+#             */
/*   Updated: 2018/12/04 22:19:04 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstpop(t_list *head, t_list *delete)
{
	if (!head || !delete)
		return ;
	while (head->next && head->next != delete)
		head = head->next;
	if (head->next == delete)
	{
		head->next = delete->next;
		free(delete->content);
		delete->next = NULL;
		free(delete);
		delete = NULL;
	}
}
