/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_checker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:03:44 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/10 19:18:13 by sadahan          ###   ########.fr       */
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
# include "dynamic.h"

typedef struct		s_file_data
{
	int				start;
	int				end;
	int				tubes;
	int				rooms;
	int				ants;
	char			*start_room;
	char			*end_room;
}					t_data;

int					check_ant_number(char *file, t_data *data);
int					check_command(t_data *data, char *file);
int					check_tubes_rooms(t_data *data, char *file);
int					check_file(char *file, t_data *data);
char				*read_file(char *str);
#endif
