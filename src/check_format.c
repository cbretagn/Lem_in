/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:29:45 by sadahan           #+#    #+#             */
/*   Updated: 2020/05/26 19:01:25 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_checker.h"
#include "../lem_in.h"

int				check_ant_number(char *file, t_data *data)
{
	int			i;
	long int	ants;
	int			zero;

	zero = 0;
	i = 0;
	ants = 0;
	while (file[i] && file[i] != '\n')
	{
		if (!ft_isdigit(file[i]))
			return (0);
		while (ft_isdigit(file[i]))
		{
			if (file[i] == '0')
				zero++;
			i++;
		}
	}
	if ((i - zero) > 10)
		return (0);
	ants = ft_atoi(file);
	if (ants == 0 || ants > 200000)
		return (0);
	data->ants = (int)ants;
	return (i);
}

int				check_command(t_data *data, char *file, int i)
{
	char		*cmd;
	int			j;

	while (file[i] && file[i] != '\n')
		i++;
	if (!(cmd = ft_strsub(file, 0, i)))
		return (0);
	if (!ft_strcmp(cmd, "##start"))
	{
		j = cmd_start(data, &file[i], 0);
		if (j == -1)
			return (ret_free_line(cmd));
		i += j;
	}
	else if (!ft_strcmp(cmd, "##end"))
	{
		j = cmd_end(data, &file[i], 0);
		if (j == -1)
			return (ret_free_line(cmd));
		i += j;
	}
	ft_strdel(&cmd);
	return ((data->start > 1 || data->end > 1) ? 0 : i);
}

int				is_room(char *line)
{
	int			i;
	int			space;

	if (line[0] == 'L')
		return (0);
	i = 0;
	space = 0;
	while (line[i])
	{
		while (line[i] != ' ' && line[i])
		{
			if (space > 0 && !(ft_isdigit(line[i]))
				&& line[i] != '-' && line[i] != '+')
				return (0);
			i++;
		}
		if (line[i] == ' ' && line[i + 1])
			space++;
		if (line[i])
			i++;
	}
	if (space != 2)
		return (0);
	return (1);
}

int				is_tube(char *line)
{
	int			i;
	int			dash;

	dash = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] != '-' && line[i])
			i++;
		if (line[i] == '-' && line[i + 1])
		{
			dash++;
			if (i == 0)
				return (0);
		}
		if (line[i])
			i++;
	}
	if (dash != 1)
		return (0);
	return (1);
}

int				check_tubes_rooms(t_data *data, char *file)
{
	int			i;
	char		*line;

	i = 0;
	while (file[i] != '\n' && file[i])
		i++;
	if (!(line = ft_strsub(file, 0, i)))
		return (0);
	if (is_room(line) > 0)
	{
		if (data->tubes > 0)
			return (ret_free_line(line));
		data->rooms++;
	}
	else if (is_tube(line) > 0)
		data->tubes++;
	else
		return (ret_free_line(line));
	ft_strdel(&line);
	return (i);
}
