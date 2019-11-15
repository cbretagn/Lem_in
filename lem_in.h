/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:42 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/15 16:35:39 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include "lem_in_checker.h"

# define BASE_DYN_NODES 10

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
}				t_anthill;

t_data			*init_struct(void);
int				next_line(char *str, int i);

int				hash_fun(char *str);
char			**put_in_table(char *str, char **tab, int size);
int				search_in_table(char *str, char **tab, int size);

t_anthill		*parser(char *str, t_anthill *anthill, int size);

t_dynode		*create_dynode(int capacity);
t_dynode		*push_int(t_dynode *node, int nb);
void			delete_dynode(t_dynode *node);
t_anthill		*create_anthill(int size);
void			delete_anthill(t_anthill *anthill);

#endif
