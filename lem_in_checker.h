/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_checker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:03:44 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/20 15:51:16 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_CHECKER_H
# define LEM_IN_CHECKER_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./libft/libft.h"
 
typedef struct      s_file_data
{
    int             start;
    int             end;
    int             tubes;
    int             rooms;
    int             ants;
    char            *start_room;
    char            *end_room;
}                   t_data;

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
int                 check_ant_number(char *file, t_data *data);
int                 check_command(t_data *data, char *file);
int                 check_tubes_rooms(t_data *data, char *file);
int					check_file(char *file, t_data *data);
char				*read_file(char *str);
#endif
