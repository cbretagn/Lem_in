/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_log_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:18:15 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 15:54:26 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

//print "file is valid"
//print "anthill created"
//print "connector graph created"
//logfile --> anthill contains X nodes, Y connectors, Z solo nodes
//logfile --> print smaller graph
//djikstra lines
//ek lines
//ek int nodes lines
//print + logfile
//Algo X selected
//print result

static void		exit_usage(void)
{
	write(1, "usage: lem-in (-v) [file_name]\n", 31);
	exit(0);
}

static void		fd_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

int				check_verbose(int argc, char **argv)
{
	if (argc < 2 || (argc == 2 && ft_strcmp(argv[1], "-v") == 0) || argc > 3)
		exit_usage();
	else if (argc == 2)
		return (NO);
	else if (argc == 3 && ft_strcmp(argv[1], "-v") == 0)
		return (YES);
	else
		exit_usage();
	return (-1);
}

void			print_anthill_log(int fd, t_anthill *anthill)
{
	int		i;
	int		j;

	fd_putstr(fd, "Simplified representation of anthill (connector nodes)\n");
	i = -1;
	while (++i < anthill->nb_room)
	{
		if (!anthill->connectors[i])
			continue ;
		j = -1;
		if (i == anthill->end || i == anthill->start)
			fd_putstr(fd, MAGENTA);
		else
			fd_putstr(fd, BLUE);
		fd_putstr(fd, anthill->rooms[i]);
		fd_putstr(fd, RES);
		fd_putstr(fd, " :");
		while (++j < anthill->connectors[i]->size)
		{
			fd_putstr(fd, " ");
			fd_putstr(fd, anthill->rooms[anthill->connectors[i]->tab[j].name]);
		}
		fd_putstr(fd, "\n");
	}
	fd_putstr(fd, "\n\n");
}
