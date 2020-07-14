/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <cbretagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 15:45:27 by cbretagn          #+#    #+#             */
/*   Updated: 2020/05/26 14:25:47 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int			check_line_nb_ant(char *buffer)
{
	int		i;

	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] > '9' || buffer[i] < '0')
			return (0);
	}
	return (1);
}

int					check_first_read(char *buffer, int ret)
{
	int		i;
	int		line;

	i = -1;
	line = 0;
	if (ret >= 4095)
		return (0);
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
			line++;
	}
	if (line == 1)
		return (1);
	return (0);
}

int					check_read_buff(char *line, int *format)
{
	char	buffer[4096];

	ft_strcpy(buffer, line);
	buffer[ft_strlen(line) - 1] = '\0';
	if (buffer[0] == '\n')
		return (0);
	if (buffer[0] == '#')
		return (1);
	if (*format == 0)
	{
		*format = 1;
		return (check_line_nb_ant(buffer));
	}
	if (*format == 1)
	{
		if (!(is_room(buffer)) && is_tube(buffer))
		{
			*format = 2;
			return (1);
		}
		return (is_room(buffer));
	}
	return (is_tube(buffer));
}

t_dstring			*check_error(int *direct_read,
							char *buff, int ret, t_dstring *file)
{
	if (*direct_read == -1)
		*direct_read = check_first_read(buff, ret);
	if (buff[0] == '\0')
		return (delete_dstring(file));
	if (!(file = push_str(file, buff)))
		exit_malloc(-2);
	if (!(check_rand(file->str)))
		return (delete_dstring(file));
	return (file);
}
