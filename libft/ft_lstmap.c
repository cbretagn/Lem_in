/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:17:18 by cbretagn          #+#    #+#             */
/*   Updated: 2018/11/21 19:36:53 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*cp;

	if (!lst || !f)
		return (NULL);
	cp = f(lst);
	new = cp;
	while (lst->next)
	{
		lst = lst->next;
		if (!(cp->next = f(lst)))
			return (NULL);
		cp = cp->next;
	}
	return (new);
}
