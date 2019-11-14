/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:42 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/14 16:06:28 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include "lem_in_checker.h"

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
	t_dynode	*nodes;
}				t_anthill;

int			hash_fun(char *str);
char		**put_in_table(char *str, char **tab, int size);
int			search_in_table(char *str, char **tab, int size);

t_anthill	*parser(char *str, t_anthill *anthill, int size);
#endif
