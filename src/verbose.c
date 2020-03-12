/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_log_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 19:18:15 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 15:01:17 by cbretagn         ###   ########.fr       */
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
