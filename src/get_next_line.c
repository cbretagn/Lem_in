/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:29:36 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/14 13:35:35 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

static char		*str_realloc(char *str, const char *append)
{
	char	*resize;
	int		size;

	size = ft_strlen(str) + ft_strlen(append);
	if (!(resize = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	resize = ft_strcpy(resize, str);
	ft_memdel((void **)&str);
	ft_strcat(resize, append);
	return (resize);
}

static char		*cut_eol(char *str, char after)
{
	char	*send;
	int		eol;
	int		len;

	eol = 0;
	while (*(str + eol) && *(str + eol) != '\n')
		eol++;
	if (after == '0')
	{
		if (!(send = ft_strnew(eol)))
			return (NULL);
		ft_memcpy(send, str, eol);
		send[eol] = '\0';
	}
	else
	{
		if (*(str + eol))
			eol++;
		len = ft_strlen(str + eol);
		if (!(send = ft_strnew(len)))
			return (NULL);
		send = ft_strcpy(send, str + eol);
		ft_strdel(&str);
	}
	return (send);
}

static t_fd		*get_fd(t_fd **head, int fd)
{
	t_fd	*send;

	send = *head;
	while (send)
	{
		if (send->fd == fd)
			return (send);
		send = send->next;
	}
	if (!(send = (t_fd *)malloc(sizeof(t_fd) * 1)))
		return (NULL);
	send->fd = fd;
	if (!(send->str = ft_strnew(1)))
		return (NULL);
	send->next = *head;
	*head = send;
	return (send);
}

static int		free_lst(t_fd **head, int fd)
{
	t_fd	*temp;
	t_fd	*del;

	temp = *head;
	if (temp->fd == fd)
	{
		free(temp->str);
		free(temp);
		return (0);
	}
	while (temp->next && temp->next->fd != fd)
		temp = temp->next;
	del = temp->next;
	temp->next = del->next;
	free(del->str);
	free(del);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_fd		*lst_offset = NULL;
	t_fd			*current_offset;
	char			*buffer;
	int				ret;

	if (fd < 0 || !(line) || !(buffer = malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	current_offset = get_fd(&lst_offset, fd);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		current_offset->str = str_realloc(current_offset->str, buffer);
		if (ft_strchr(current_offset->str, '\n'))
			break ;
	}
	if (ret == -1)
		return (-1);
	ft_memdel((void **)&buffer);
	if (ret < BUFF_SIZE && !ft_strlen((current_offset->str)))
		return (free_lst(&lst_offset, fd));
	*line = cut_eol(current_offset->str, '0');
	current_offset->str = cut_eol(current_offset->str, '1');
	return (1);
}
