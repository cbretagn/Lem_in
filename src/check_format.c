/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:29:45 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/15 15:50:46 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_checker.h"
#include "../lem_in.h"

int			check_ant_number(char *file, t_data *data)
{
	int		i;

	i = 0;
	while (file[i] && file[i] != '\n')
	{
		if (!ft_isdigit(file[i]))
			return (0);
		while (ft_isdigit(file[i]))
			i++;
	}
	data->ants = ft_atoi(file);
	return (i);
}

int			check_command(t_data *data, char *file)
{
	int		i;
	char	*cmd;
	int		j;

	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	j = i;
	while (file[j] && file[j + 1] != ' ')
		j++;
	if (!(cmd = ft_strsub(file, 0, i)))
		return (0);
	if (!ft_strcmp(cmd, "##start"))
	{
		data->start++;
		if (!(data->start_room = ft_strsub(file, i + 1, j - i)))
			return (0);
	}
	else if (!ft_strcmp(cmd, "##end"))
	{
		data->end++;
		if (!(data->end_room = ft_strsub(file, i + 1, j - i)))
			return (0);
	}
	return ((data->start > 1 || data->end > 1) ? 0 : i); 
}

static int	is_room(char *line)
{
	int		i;
	int		space;

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
		i++;
	}
	if (space != 2)
		return (0);
	return (1);
}

static int	is_tube(char *line)
{
	char	**tube;

	if (!(tube = ft_strsplit(line, '-')))
		return (0);
	if (tube[2] || !tube[1])
	{
		write(1, "Tube format invalid\n", 20);
		return (0);
	}
	return (1);
}

int			check_tubes_rooms(t_data *data, char *file)
{
	int		i;
	char	*line;

	i = 0;
	while (file[i] != '\n' && file[i])
		i++;
	if (!(line = ft_strsub(file, 0, i)))
		return (0);
	if (is_room(line) > 0)
	{
		if (data->tubes > 0)
			return (0);
		data->rooms++;
	}
	else if (is_tube(line) > 0)
		data->tubes++;
	else
		return (0);
	return (i);
}
