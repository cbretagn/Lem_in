/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:38:10 by cbretagn          #+#    #+#             */
/*   Updated: 2020/05/27 11:08:18 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		fd_putstr(int fd, char *str)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void			print_routes_log(int fd, t_path *routes, int lines, char *str)
{
	char		*tmp;

	if (fd == NO || fd < 0)
		return ;
	fd_putstr(fd, GREEN);
	fd_putstr(fd, str);
	fd_putstr(fd, RES);
	if (routes->path_length[0] == 1)
	{
		fd_putstr(fd,
				"Start and end connected, all ants can travel in one step\n");
		return ;
	}
	else
	{
		fd_putstr(fd, BLUE);
		fd_putstr(fd, "Nb lines ");
		tmp = ft_itoa(lines);
		fd_putstr(fd, tmp);
		fd_putstr(fd, "\n");
		fd_putstr(fd, RES);
		ft_strdel(&tmp);
	}
}

int				cmd_start(t_data *data, char *file, int i)
{
	int			j;

	data->start++;
	if (data->start > 1)
		return (-1);
	i += fix_comments(&file[i], 0);
	j = i;
	while (file[j] && file[j + 1] != ' ')
		j++;
	if (!(data->start_room = ft_strsub(file, i + 1, j - i)))
		return (-1);
	return (i);
}

int				cmd_end(t_data *data, char *file, int i)
{
	int			j;

	data->end++;
	if (data->end > 1)
		return (-1);
	i += fix_comments(&file[i], 0);
	j = i;
	while (file[j] && file[j + 1] != ' ')
		j++;
	if (!(data->end_room = ft_strsub(file, i + 1, j - i)))
		return (-1);
	return (i);
}

int				fix_comments(char *file, int i)
{
	int			j;
	char		*comment;

	comment = NULL;
	while (file[i + 1] && file[i + 1] == '#')
	{
		j = i;
		i++;
		while (file[i] && file[i] != '\n')
			i++;
		if (!(comment = ft_strsub(file, j + 1, i - j - 1)))
			return (0);
		if (!ft_strcmp(comment, "##start") || !ft_strcmp(comment, "##end"))
		{
			ft_strdel(&comment);
			return (-1);
		}
		ft_strdel(&comment);
	}
	return (i);
}
