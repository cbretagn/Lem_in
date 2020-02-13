/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:36:57 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/12 19:13:05 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int	next_unoccupied(t_pos ant, int *occupied, t_anthill *anthill, int **matrix)
{
	int		i;
	int		curr;
	int		next;

	i = -1;
	curr = ant.curr;
	if (ant.hub == YES)
	{
		while (++i < anthill->nb_room)
		{
			if (matrix[curr][i] != -1 && matrix[i][curr] == -1 
					&& (occupied[matrix[curr][i]] == NO 
						|| matrix[curr][i] == anthill->end))
				return (matrix[curr][i]);
		}
	}
	else
	{
		if (anthill->nodes[curr]->tab[0] == ant.prev)
			next = anthill->nodes[curr]->tab[1];
		else
			next = anthill->nodes[curr]->tab[0];
		if (occupied[next] == NO || next == anthill->end)
			return (next);
	}
	return (-1);
}

static int	one_step(t_pos *all_ants, t_anthill *anthill, int *occupied,
						int **matrix)
{
	int		i;
	int		arrived;
	int		next;

	i = -1;
	arrived = 0;
	while (++i < anthill->ants)
	{
		if (all_ants[i].curr == anthill->end)
			continue ;
		next = next_unoccupied(all_ants[i], occupied, anthill, matrix);
		if (next != -1)
		{
			all_ants[i].prev = all_ants[i].curr;
			all_ants[i].curr = next;
			if (anthill->connectors[all_ants[i].curr])
				all_ants[i].hub = YES;
			else
				all_ants[i].hub = NO;
			all_ants[i].move = YES;
			if (all_ants[i].curr == anthill->end)
				arrived++;
		}
		else
			all_ants[i].move = NO;
	}
	return (arrived);
}

t_dstring	*print_line(t_pos *all_ants, t_anthill *anthill, t_dstring *print)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < anthill->ants)
	{
		if (all_ants[i].move == NO)
			continue ;
		print = push_str(print, "L");
		tmp = ft_itoa(i + 1);
		print = push_str(print, tmp);
		ft_strdel(&tmp);
		print = push_str(print, "-");
		print = push_str(print, anthill->rooms[all_ants[i].curr]);
		print = push_str(print, " ");
	}
	print = push_str(print, "\n");
	return (print);
}

t_dstring	*move_ants(t_pos *all_ants, t_anthill *anthill, int *occupied,
					int **matrix)
{
	t_dstring	*ret;
	int			arrived;

	arrived = 0;
	if (!(ret = create_dstring(10000, "")))
		exit(-1);
	while (arrived != anthill->ants)
	{
		arrived += one_step(all_ants, anthill, occupied, matrix);
		anthill->lines += 1;
		ret = print_line(all_ants, anthill, ret);
	}
	return (ret);
}

t_dstring	*print_ek(t_anthill *anthill, int **matrix)
{
	t_dstring	*ret;
	t_pos		*all_ants;
	int			*occupied;
	int			i;

	if (!(all_ants = (t_pos *)malloc(sizeof(t_pos) * anthill->ants)))
		exit(-1);
	if (!(occupied = (int *)malloc(sizeof(int) * anthill->nb_room)))
		exit(-1);
	i = -1;
	while (++i < anthill->nb_room)
		occupied[i] = NO;
	i = -1;
	while (++i < anthill->ants)
	{
		all_ants[i].prev = anthill->start;
		all_ants[i].curr = anthill->start;
		all_ants[i].move = NO;
		all_ants[i].hub = YES;
	}
	anthill->lines = 0;
	ret = move_ants(all_ants, anthill, occupied, matrix);
	printf("nb of lines is %d\n", anthill->lines);
	return (ret);
}
