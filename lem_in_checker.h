/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_checker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:03:44 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/13 15:04:19 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_CHECKER_H
# define LEM_IN_CHECKER_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
 
typedef struct      s_bool
{
    int start;
    int end;
    int tubes;
    int rooms;
}                   t_bool;

typedef struct		s_dstring
{
	unsigned int	size;
	unsigned int	capacity;
	char			*str;
}					t_dstring;

t_dstring			*create_dstring(unsigned int cap, char *str);
void				delete_dstring(t_dstring *del);
t_dstring			*push_str(t_dstring *dest, char *src);
t_dstring			*push_str_nchar(t_dstring *dest, char *src, int n);
void				delete_dstring(t_dstring *del);
int                 check_ant_number(char *file);
int                 check_command(t_bool *b, char *file);
int                 check_tubes_rooms(t_bool *b, char *file);

#endif