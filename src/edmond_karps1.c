/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karps1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:52:11 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/12 18:51:42 by cbretagn         ###   ########.fr       */
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
			capacity_matrix[i][j] = -1;
	}
	return (capacity_matrix);
}


static void		check_neighbours2(t_anthill *anthill, t_dijkstra *tab, int curr,
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
				|| capacity_matrix[curr][next] != -1)
			continue ;
		else
		{
			if (tab[next].dist > distance + tab[curr].dist)
			{
				tab[next].prev = curr;
				tab[next].dist = distance + tab[curr].dist;
			}
		}
	}
}

//while i != end check neighbours, mark as visited choose next one (closest)
//repeat

static int		find_min_dist(t_dijkstra *tab, int size)
{
	int		ret;
	int		dist;
	int		i;

	i = -1;
	dist = INT_MAX;
	ret = -1;
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
		check_neighbours2(anthill, tab, curr, matrix);
		tab[curr].visited = VISITED;
		curr = find_min_dist(tab, anthill->nb_room);
		if (curr == -1)
			return (-1);
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

static void		update_matrix(int **matrix, t_dijkstra *table, t_anthill *anthill)
{
	int		node;
	int		from;

	node = anthill->end;
	while (node != anthill->start)
	{
		from = 0;
		while (anthill->connectors[table[node].prev]->tab[from].name != node)
			from++;
		matrix[table[node].prev][node] 
			= anthill->connectors[table[node].prev]->tab[from].from;;
		node = table[node].prev;
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

static void		print_paths(int **matrix, t_anthill *anthill)
{
	int		node;
	int		i;
	int		j;

	i = -1;
	while (++i < anthill->nb_room)
	{
		if (matrix[anthill->start][i] != -1 && matrix[i][anthill->start] == -1)
		{
			printf("\n");
			printf("start %d -> %d from %d ", anthill->start, i, matrix[anthill->start][i]);
			node = i;
			while (node != anthill->end)
			{
				j = -1;
				while (++j < anthill->nb_room)
				{
					if (matrix[node][j] != -1 && matrix[j][node] == -1)
					{
						printf("then %d from %d ", j, matrix[node][j]);
						node = j;
						break ;
					}
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
	int				ret;

	if (!(matrix = create_capacity_matrix(anthill->nb_room)))
		exit(-1);
	if (!(tab = (t_dijkstra *)malloc(sizeof(t_dijkstra) * anthill->nb_room)))
		exit(-1);
	while (42)
	{
		init_table(tab, anthill);
		ft_putstr("hey\n");
		ret = dijkstra(anthill, tab, matrix);
		printf("ret is %d\n", ret);
		if (ret == -1)
			break ;
		update_matrix(matrix, tab, anthill);
	}
	//print_matrix(matrix, anthill->nb_room);
	//print_paths(matrix, anthill);
	t_path	*routes = get_paths(anthill, matrix);
	return (matrix);
}

