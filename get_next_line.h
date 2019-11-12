/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:13:55 by cbretagn          #+#    #+#             */
/*   Updated: 2019/05/02 14:39:52 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096

int					get_next_line(const int fd, char **line);

typedef struct		s_fd
{
	int				fd;
	char			*str;
	struct s_fd		*next;
}					t_fd;

#endif
