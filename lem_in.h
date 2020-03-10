/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:42 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/10 17:13:31 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "dynamic.h"
# include <unistd.h>
# include <stdlib.h>
# include "lem_in_checker.h"

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
# define MAX_ANT 100000

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
	t_dynode	**inter_nodes;
	t_connector	**connectors;
}				t_anthill;

t_data			*init_struct(void);
void			free_data(t_data *data);
int				next_line(char *str, int i);

long int		hash_fun(char *str);
char			**put_in_table(char *str, char **tab, int size);
int				search_in_table(char *str, char **tab, int size);

t_anthill		*parser(char *str, t_anthill *anthill, t_data *data);
t_anthill		*handle_tubes(t_anthill *anthill, char *str, int i,
					t_dstring *word);

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
t_path			*get_route(t_path *routes, t_dijkstra *tab, int end,
					t_anthill *anthill);
void			rec_dijkstra(t_anthill *anthill, t_dijkstra *tab);
void			check_neighbours(t_anthill *anthill, t_dijkstra *tab, int curr);
int				compute_stop(t_path *routes, int ants);

t_path			*get_nb_ants(t_path *routes, int nb_ants);

t_path			*get_paths(t_anthill *anthill, int **matrix);
t_path			*sort_routes(t_path *routes);

int				nb_lines(t_path *routes);
int				**init_matrice(int size, int nb);
int				**init_mat_capacity(t_anthill *a);
t_path			*edmonds_karp1(t_anthill *a);
t_path			*edmonds_karp2(t_anthill *a);
int				*init_parent(int size);
t_path			*reverse_paths(t_path *path);

void			add_to_top(t_pile *pile, int data);
t_pile			*init_pile(int data);
int				del_pile(t_pile *pile);
int				del_bottom(t_pile *pile);

void			update_paths(t_path *path, int v, int i);
void			reset_parent(int *parent, int size, t_anthill *a);
t_pile			*proceed(int v, t_anthill *a, t_pile *queue);
void			update_residual_graph(int v, t_anthill *a, int **res);

int				is_visited(int node, t_dynode *list);
void			print_direct(t_anthill *anthill);
t_path			*get_direct_path(t_path *routes, t_anthill *anthill);
t_path			*get_real_routes(t_path *routes, t_anthill *anthill);

void			print_ants(t_anthill *anthill, t_path *routes);
int				nb_path_to_use(t_path *routes);

t_dijkstra		*init_dijkstra_tab(t_dijkstra *tab, t_anthill *anthill);
t_dijkstra		*refresh_tab(t_dijkstra *tab, t_anthill *anthill);

void			debugger(t_path *routes, t_anthill *anthill, char *name);
#endif
