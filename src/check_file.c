/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:57:05 by sadahan           #+#    #+#             */
/*   Updated: 2020/03/12 18:21:15 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_checker.h"

t_data			*init_struct(void)
{
	t_data		*data;

	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
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
			if ((j = check_command(data, &file[i])) == 0)
				return (check_return(i, data));
		}
		else if ((j = check_tubes_rooms(data, &file[i])) == 0)
			return (check_return(i, data));
		i += j;
	}
	return (check_return(i, data));
}

t_dstring		*read_file(char *str)
{
	int			fd;
	int			ret;
	char		buff[4096];
	t_dstring	*file;

	file = NULL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit(-2);
	if (!(file = create_dstring(4096, "")))
		return (NULL);
	while ((ret = read(fd, buff, 4095)))
	{
		if (ret == -1)
			exit(-2);
		buff[ret] = '\0';
		if (buff[0] == '\0')
			exit(-2);
		if (!(file = push_str(file, buff)))
			return (NULL);
	}
	close(fd);
	if (!file->str)
		exit(-2);
	return (file);
}
