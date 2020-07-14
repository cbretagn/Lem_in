/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_log_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:18:15 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 18:48:00 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		exit_usage(void)
{
	write(1, "usage: lem-in (-v) < [file_name]\n", 33);
	exit(0);
}

static void		fd_putstr(char *str, int fd)
{
	if (fd == NO)
		return ;
	write(fd, str, ft_strlen(str));
}

int				check_verbose(int argc, char **argv)
{
	if (argc == 1)
		return (NO);
	else if (argc == 2 && ft_strcmp(argv[1], "-v") == 0)
		return (YES);
	else
		exit_usage();
	return (-1);
}

void			print_anthill_log(int fd, t_anthill *anthill)
{
	int		i;
	int		j;

	fd_putstr("Simplified representation of anthill (connector nodes)\n", fd);
	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!anthill->connectors[i])
			continue ;
		j = -1;
		if (i == anthill->end || i == anthill->start)
			fd_putstr(MAGENTA, fd);
		else
			fd_putstr(BLUE, fd);
		fd_putstr(anthill->rooms[i], fd);
		fd_putstr(RES, fd);
		fd_putstr(" :", fd);
		while (++j < anthill->connectors[i]->size)
		{
			fd_putstr(" ", fd);
			fd_putstr(anthill->rooms[anthill->connectors[i]->tab[j].name], fd);
		}
		fd_putstr("\n", fd);
	}
	fd_putstr("\n\n", fd);
}

int				check_rand(char *file)
{
	int			i;

	i = 0;
	while (i < 10)
	{
		if (!ft_isascii(file[i]))
			return (0);
		i++;
	}
	return (1);
}
