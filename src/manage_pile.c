/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:56:50 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/12 18:18:54 by sadahan          ###   ########.fr       */
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
	{
		new->prev = NULL;
		pile->bottom = new;
	}
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
		exit_malloc(-2);
	if (!(element = malloc(sizeof(t_element))))
		exit_malloc(-2);
	element->nb = data;
	element->next = NULL;
	element->prev = NULL;
	pile->top = element;
	pile->bottom = element;
	pile->nb_elem = 1;
	return (pile);
}

void				del_pile(t_pile *pile)
{
	t_element	*tmp;

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
