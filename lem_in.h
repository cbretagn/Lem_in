/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:42 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/27 16:48:28 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "get_next_line.h"
# include "dynamic.h"
# include <unistd.h>
# include <stdlib.h>
# include "lem_in_checker.h"
# include <stdio.h>

# define NB_ROOM anthill->nb_room
# define ROOMS anthill->rooms
# define NODES anthill->nodes
# define CONNECTORS anthill->connectors
# define BASE_DYN_NODES 10
# define BASE_CONNECTORS 10
# define VISITED 1
# define NOTVIS 0
# define NAN -1
# define NO 1
# define YES 0
# define DIRECT -1

typedef struct	s_dijkstra
{
	int			prev;
	int			dist;
	int			visited;
}				t_dijkstra;

typedef struct	s_vertex
{
	int			name;
	int			from;
	int			dist;
}				t_vertex;

typedef struct	s_connector
{
	t_vertex	*tab;
	int			size;
	int			cap;
}				t_connector;

typedef struct	s_dynode
{
	int			*tab;
	int			size;
	int 		cap;
}			 	t_dynode;

typedef struct	s_path
{
	int			size;
	int			cap;
	int			*path_length;
	int			*nb_ants;
	t_dynode	**tab;
}				t_path;

typedef struct	s_ants
{
	int			*path;
	int			*curr;
	int			*room;
	int			nb_lines;
	int			path_to_use;
	int			arrived;
}				t_ants;

typedef struct	s_pos
{
	int			prev;
	int			curr;
	int			hub;
	int			move;
}				t_pos;

//replace char **rooms dans anthill to add coordinates
// typedef struct	s_rooms
// {
// 	char		*rooms;
// 	int			*x;
// 	int			*y;
// }				t_rooms;

// typedef struct	s_edges
// {
// 	int			from;
// 	int			to;
// 	int			flow;
// 	int			dist;
// 	int			visited;
// }				t_edges;

typedef	struct		s_elem
{
	int				nb;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_element;

typedef	struct	s_pile
{
	t_element	*top;
	t_element	*bottom;
	int			nb_elem;
}				t_pile;

typedef struct	s_anthill
{
	int			ants;
	char		**rooms;
	int			nb_room;
	int			nb_tubes;
	int			start;
	int			end;
	int			lines;
	t_dynode	**nodes;
	t_connector	**connectors;
}				t_anthill;

t_data			*init_struct(void);
void			free_data(t_data *data);
int				next_line(char *str, int i);

int				hash_fun(char *str);
char			**put_in_table(char *str, char **tab, int size);
int				search_in_table(char *str, char **tab, int size);

t_anthill		*parser(char *str, t_anthill *anthill, t_data *data);

t_dynode		*create_dynode(int capacity);
t_dynode		*push_int(t_dynode *node, int nb);
void			delete_dynode(t_dynode *node);
t_anthill		*create_anthill(int size);
void			delete_anthill(t_anthill *anthill);

t_connector		*create_connector(int size);
void			delete_connector(t_connector *del);
t_connector		*push_vertex(t_connector *connector, int room, int distance,
							int from);

t_anthill		*create_connector_graph(t_anthill *anthill);

t_path			*next_shortest_path(t_anthill *anthill);
t_path			*create_path_tab(int size);
void			delete_path_tab(t_path *del);
int				find_min(t_dijkstra *tab, int size);
t_path			*get_route(t_path *routes, t_dijkstra *tab, int end, int start, t_anthill *anthill);
void			rec_dijkstra(t_anthill *anthill, t_dijkstra *tab);
void			check_neighbours(t_anthill *anthill, t_dijkstra *tab, int curr);
int				compute_stop(t_path *routes, int ants);

t_path			*get_nb_ants(t_path *routes, int nb_ants);


void			print_suggestions(t_anthill *anthill);
t_path			*superposition_path(t_anthill *anthill, int node);
void			shortest_path_to(t_anthill *anthill, t_dijkstra *tab, int node);

int				**edmond_karps(t_anthill *anthill);
t_path			*get_paths(t_anthill *anthill, int **matrix);
t_path			*handle_collision(t_path *routes, t_anthill *anthill);
t_path			*sort_routes(t_path *routes);

t_dstring		*print_ek(t_anthill *anthill, int **matrix);

int				nb_lines(t_path *routes);
// void     		print_path(char *graph, t_path *path, t_anthill *anthill);
int				**init_matrice(t_anthill *a);
t_path			*edmonds_karp(t_anthill *a);
//void			print_matrix(int **res, int size);
int		*init_parent(t_anthill *a);
// t_dijkstra				*init_parent(t_anthill *a);
void			add_to_top(t_pile *pile, int data);
t_pile			*init_pile(int data);
int				del_pile(t_pile *pile);
int				del_bottom(t_pile *pile);

int				is_visited(int node, t_dynode *list);
void			print_direct(t_anthill *anthill);
t_path			*get_direct_path(t_path *routes, t_anthill *anthill);
t_path			*get_real_routes(t_path *routes, t_anthill *anthill);

void			print_ants(t_anthill *anthill, t_path *routes);
int				nb_path_to_use(t_path *routes);


t_dynode		**create_false_nodes(t_anthill *a);
#endif
