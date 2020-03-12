/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:38:10 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 15:51:38 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void		print_routes_log(int fd, t_path *ek, t_path *ek_int, t_path *dj)
{
	int		nb_ek;
	int		nb_ekint;
	int		nb_dj;

	if (ek->path_length[0] == 1 || ek_int->path_length[0] == 1 
			|| dj->path_length[0] == 1)
	{
		fd_putstr(fd, "Start and end are connected, all ants can travel in one
				step\n");
		return ;
	}
