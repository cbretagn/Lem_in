/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:56:50 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/05 16:21:10 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void			add_to_top(t_pile *pile, int data)
{
	t_element	*new;

	new = NULL;
	if (!pile)
		exit(EXIT_FAILURE);
	if (!(new = malloc(sizeof(t_element))))
		exit(EXIT_FAILURE);
	new->nb = data;
	if (pile->nb_elem == 0)
		new->prev = NULL;
	else
	{
		pile->top->next = new;
		new->prev = pile->top;
	}
	new->next = NULL;
	pile->top = new;
	pile->nb_elem++;
}

t_pile			*init_pile(int data)
{
	t_pile		*pile;
	t_element	*element;

	if (!(pile = malloc(sizeof(t_pile))))
		return (NULL);
	if (!(element = malloc(sizeof(t_element))))
		return (NULL);
	element->nb = data;
	element->next = NULL;
	element->prev = NULL;
	pile->top = element;
	pile->bottom = element;
	pile->nb_elem = 1;
	return (pile);
}

int				del_pile(t_pile *pile)
{
	int			data;
	t_element	*tmp;

	if (!pile)
		return (0);
	data = pile->top->nb;
	while (pile->top)
	{
		tmp = pile->top;
		pile->top = pile->top->prev;
		free(tmp);
		tmp = NULL;
	}
	pile->nb_elem = 0;
	free(pile);
	pile = NULL;
	return (data);
}

int				del_bottom(t_pile *pile)
{
	int			data;
	t_element	*temp;

	if (!pile)
		return (-1);
	data = pile->bottom->nb;
	if (pile->nb_elem > 1)
	{
		temp = pile->bottom->next;
		temp->prev = NULL;
		free(pile->bottom);
		pile->bottom = NULL;
		pile->bottom = temp;
		pile->nb_elem--;
		return (data);
	}
	else if (pile->nb_elem == 1)
	{
		free(pile->bottom);
		pile->bottom = NULL;
		pile->top = NULL;
		pile->nb_elem--;
		return (data);
	}
	return (-1);
}
