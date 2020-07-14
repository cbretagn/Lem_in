/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_checker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <cbretagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:03:44 by sadahan           #+#    #+#             */
/*   Updated: 2020/05/26 12:16:08 by cbretagn         ###   ########.fr       */
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
int					check_command(t_data *data, char *file, int i);
int					check_tubes_rooms(t_data *data, char *file);
int					check_file(char *file, t_data *data);
int					is_room(char *line);
int					is_tube(char *line);
int					check_read_buff(char *buffer, int *format);
int					check_first_read(char *buffer, int ret);
t_dstring			*check_error(int *direct_read,
						char *buff, int ret, t_dstring *file);
t_dstring			*read_file();
#endif
