/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:57:05 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/12 18:25:18 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_checker.h"

static t_bool	*init_struct(void)
{
	t_bool		*b;

	if (!(b = malloc(sizeof(t_bool))))
		return (NULL);
	b->end = 0;
	b->start = 0;
	b->tubes = 0;
	b->rooms = 0;
	return (b);
}

static int		check_return(int i, t_bool *b)
{
	if (b->start == 0 || b->end == 0 || b->tubes == 0 || b->rooms < 2)
	{
		write(1, "No path, start or end\n", 22);
		return (0);
	}
	return (i);
}

static int		check_file(char *file)
{
	int			i;
	int			j;
	t_bool		*b;

	i = 0;
	j = 0;
	if (!(b = init_struct()))
		return (0);
	if (!(i = check_ant_number(file)))
		return (0);
	while (file[++i])
	{
		if (!file[i] || (file[i] == '\n'))
			return (check_return(i, b));
		if (file[i] == '#')
		{
			if ((j = check_command(b, &file[i])) == 0)
				return (check_return(i, b));
		}
		else if ((j = check_tubes_rooms(b, &file[i])) == 0)
			return (check_return(i, b));
		i += j;
	}
	return (check_return(i, b));
}

static char		*read_file(char *str)
{
	int			fd;
	int			ret;
	char		buff[4096];
	char		*file;

	fd = open(str, O_RDONLY);
	if (!(file = ft_strnew(0)))
		return (NULL);
	if (fd != -1)
	{
		while ((ret = read(fd, buff, 4095)))
		{
			buff[ret] = '\0';
			if (!(file = ft_strnjoin_free(file, buff, ret)))
				return (NULL);
		}
	}
	return (file);
}

int				main(int argc, char **argv)
{
	char		*file;
	char		*graph;

	if (argc != 2)
	{
		write(1, "Not enough arguments\n", 21);
		return (0);
	}
	if (!(file = read_file(argv[1])))
		return (0);
	if (!(graph = ft_strsub(file, 0, check_file(file))))
		return (0);
	printf("%s", graph);
	return (1);
}
