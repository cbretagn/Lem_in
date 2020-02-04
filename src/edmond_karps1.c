/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karps1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:52:11 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/04 18:22:50 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// adjency list undirected graph
// capacity matrix residual graph (bool)
//
// djikstra to find shortest path which is an augmenting path ie 1 on 
// residual flow matrix all along
//
// update graph
//
// keep searching until no augmenting path found
// return condition ?
//

#include "../lem_in.h"
#include <limits.h>

int			**create_capacity_matrix(int nb)
{
	int		**capacity_matrix;
	int		i;
	int		j;

	i = -1;
	if (!(capacity_matrix = (int **)malloc(sizeof(int *) * nb)))
		exit(-1);
	while (++i < nb)
	{
		if (!(capacity_matrix[i] = (int *)malloc(sizeof(int) * nb)))
			exit(-1);
	}
	i = -1;
	while (++i < nb)
	{
		j = -1;
		while (++j < nb)
			capacity_matrix[i][j] = 1;
	}
	return (capacity_matrix);
}


static int		check_neighbours2(t_anthill *anthill, t_dijkstra *tab, int curr,
									int **capacity_matrix)
{
	int		i;
	int		next;
	int		distance;
	int		found;

	i = -1;
	found = 0;
	while (++i < CONNECTORS[curr]->size)
	{
		next = CONNECTORS[curr]->tab[i].name;
		distance  = CONNECTORS[curr]->tab[i].dist;
		if (tab[next].visited == VISITED || tab[next].visited == NAN
				|| capacity_matrix[curr][next] < 1)
			continue ;
		else
		{
			if (tab[next].dist > distance + tab[curr].dist)
			{
				tab[next].prev = curr;
				tab[next].dist = distance + tab[curr].dist;
			}
			found++;
		}
	}
	return (found);
}

//while i != end check neighbours, mark as visited choose next one (closest)
//repeat

static int		find_min_dist(t_dijkstra *tab, int size, int curr, int **matrix)
{
	int		ret;
	int		dist;
	int		i;

	i = -1;
	dist = INT_MAX;
	while (++i < size)
	{
		if (tab[i].visited != NOTVIS)
			continue ;
		if (tab[i].dist < dist)
		{
			ret = i;
			dist = tab[i].dist;
		}
	}
	return (ret);
}

static int		dijkstra(t_anthill *anthill, t_dijkstra *tab, int **matrix)
{
	int		curr;

	curr = anthill->start;
	while (curr != anthill->end)
	{
		if (check_neighbours2(anthill, tab, curr, matrix) == 0)
			return (0);
		tab[curr].visited = VISITED;
		curr = find_min_dist(tab, anthill->nb_room, curr, matrix);
	}
	return (1);
}

static void		init_table(t_dijkstra *tab, t_anthill *anthill)
{
	int		i;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!(anthill->connectors[i]))
			tab[i].visited = NAN;
		else
			tab[i].visited = NOTVIS;
		tab[i].dist = INT_MAX;
	}
	tab[anthill->start].prev = anthill->start;
	tab[anthill->start].dist = 0;
}

static void		update_matrix(int **matrix, t_dijkstra *tab, t_anthill *anthill)
{
	int		node;

	node = anthill->end;
	while (node != anthill->start)
	{
		matrix[tab[node].prev][node] -= 1;
		node = tab[node].prev;
	}
}

static void		print_matrix(int **matrix, int nb)
{
	int		i;
	int		j;

	i = -1;
	while (++i < nb)
	{
		j = -1;
		while (++j < nb)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

static void		print_paths(int **matrix, t_dijkstra *tab, t_anthill *anthill)
{
	int		curr;
	int		next;

	init_table(tab, anthill);
	while (42)
	{
		printf("\n");
		curr = anthill->start;
		while (curr != anthill->end)
		{
			printf("%d ", curr);
			int	i = -1;
			while (++i < anthill->connectors[curr]->size)
			{
				next = anthill->connectors[curr]->tab[i].name;
				if (tab[next].visited != NOTVIS)
					continue ;
				if (matrix[curr][next] == 0 && matrix[next][curr] != 0)
				{
					printf("%d ", next);
					curr = next;
					tab[curr].visited = VISITED;
				}
			}
		}
	}
}

		//parcourir noeud adjacent
		// then if 0 on one edge out of two mark it then keep going


int				**edmond_karps(t_anthill *anthill)
{
	int				**matrix;
	t_dijkstra 		*tab;

	if (!(matrix = create_capacity_matrix(anthill->nb_room)))
		exit(-1);
	if (!(tab = (t_dijkstra *)malloc(sizeof(t_dijkstra) * anthill->nb_room)))
		exit(-1);
	while (42)
	{
		init_table(tab, anthill);
		if ((dijkstra(anthill, tab, matrix) == 0))
			break ;
		update_matrix(matrix, tab, anthill);
	}
	print_matrix(matrix, anthill->nb_room);
	print_paths(matrix, tab, anthill);
	return (matrix);
}

