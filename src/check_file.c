/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:57:05 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/15 13:14:23 by sadahan          ###   ########.fr       */
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
	return (data);
}

static int		check_return(int i, t_data *data)
{
	if (data->start == 0 || data->end == 0
		|| data->tubes == 0 || data->rooms < 2)
	{
		write(1, "No path, start or end\n", 22);
		return (0);
	}
	return (i);
}

int				check_file(char *file, t_data *data)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
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

char			*read_file(char *str)
{
	int			fd;
	int			ret;
	char		buff[4096];
	t_dstring	*file;

	file = NULL;
	fd = open(str, O_RDONLY);
	if (fd != -1)
	{
		while ((ret = read(fd, buff, 4095)))
		{
			buff[ret] = '\0';
			if (!file)
			{
				if (!(file = create_dstring(4096, buff)))
					return (NULL);
			}
			else if (!(file = push_str(file, buff)))
				return (NULL);
		}
	}
	close(fd);
	return (file->str);
}

// int				main(int argc, char **argv)
// {
// 	char		*file;
// 	char		*graph;
// 	t_data		*data;

// 	if (!(data = init_struct()))
// 		return (0);
// 	if (argc != 2)
// 	{
// 		write(1, "Not enough arguments\n", 21);
// 		return (0);
// 	}
// 	if (!(file = read_file(argv[1])))
// 		return (0);
// 	if (!(graph = ft_strsub(file, 0, check_file(file, data))))
// 		return (0);
// 	return (1);
// }
