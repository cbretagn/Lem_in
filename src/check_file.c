/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <cbretagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:57:05 by sadahan           #+#    #+#             */
/*   Updated: 2020/05/26 13:23:10 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_data			*init_struct(void)
{
	t_data		*data;

	if (!(data = malloc(sizeof(t_data))))
		exit_malloc(-2);
	data->end = 0;
	data->start = 0;
	data->tubes = 0;
	data->rooms = 0;
	data->ants = 0;
	data->start_room = NULL;
	data->end_room = NULL;
	return (data);
}

void			free_data(t_data *data)
{
	ft_strdel(&data->start_room);
	ft_strdel(&data->end_room);
	free(data);
	data = NULL;
}

static int		check_return(int i, t_data *data)
{
	if (data->start == 0 || data->end == 0
		|| data->tubes == 0 || data->rooms < 2)
		return (0);
	return (i);
}

int				check_file(char *file, t_data *data)
{
	int			i;
	int			j;

	if (!(i = check_ant_number(file, data)))
		return (0);
	while (file[++i])
	{
		if (!file[i] || (file[i] == '\n'))
			return (check_return(i, data));
		if (file[i] == '#')
		{
			if ((j = check_command(data, &file[i], 0)) == 0)
				return (check_return(i, data));
		}
		else if ((j = check_tubes_rooms(data, &file[i])) == 0)
			return (check_return(i, data));
		i += j;
	}
	return (check_return(i, data));
}

t_dstring		*read_file(void)
{
	ssize_t		ret;
	char		buff[4096];
	t_dstring	*file;
	int			format;
	int			direct_read;

	file = NULL;
	format = 0;
	direct_read = -1;
	if (!(file = create_dstring(4096, "")))
		exit_malloc(-2);
	while ((ret = read(0, buff, 4095)))
	{
		if (ret == -1)
			return (delete_dstring(file));
		buff[ret] = '\0';
		file = check_error(&direct_read, buff, ret, file);
		if (direct_read == 1 && !check_read_buff(buff, &format))
			break ;
	}
	if (!file->str)
		return (delete_dstring(file));
	return (file);
}
