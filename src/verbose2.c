/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:38:10 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 19:25:08 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		fd_putstr(int fd, char *str)
{
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
