/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:42 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/26 11:15:43 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include "lem_in_checker.h"

# define NB_ROOM anthill->nb_room
# define ROOMS anthill->rooms
# define NODES anthill->nodes
# define CONNECTORS anthill->connectors
# define BASE_DYN_NODES 10
# define BASE_CONNECTORS 10

typedef struct	s_vertex
{
	int			name;
	int			dist;
	int			flow;
	int			cap_flow;
}				t_vertex;

typedef struct s_connector
{
	t_vertex	*tab;
	int			size;
	int			cap;
	int			xflow;
	int			height;
}				t_connector;

typedef struct	s_dynode
{
	int			*tab;
	int			size;
	int 		cap;
}			 	t_dynode;

typedef struct s_anthill
{
	int			ants;
	char		**rooms;
	int			nb_room;
	int			nb_tubes;
	int			start;
	int			end;
	t_dynode	**nodes;
	t_connector	**connectors;
}				t_anthill;

t_data			*init_struct(void);
int				next_line(char *str, int i);

int				hash_fun(char *str);
char			**put_in_table(char *str, char **tab, int size);
int				search_in_table(char *str, char **tab, int size);

t_anthill		*parser(char *str, t_anthill *anthill, int size, t_data *data);

t_dynode		*create_dynode(int capacity);
t_dynode		*push_int(t_dynode *node, int nb);
void			delete_dynode(t_dynode *node);
t_anthill		*create_anthill(int size, t_data *data);
void			delete_anthill(t_anthill *anthill);

t_connector		*create_connector(int size);
void			delete_connector(t_connector *del);
t_connector		*push_vertex(t_connector *connector, int room, int distance);

t_anthill		*create_connector_graph(t_anthill *anthill);

void			init_preflow(t_anthill *anthill);
#endif
