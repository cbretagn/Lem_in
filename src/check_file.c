/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:57:05 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/14 17:13:13 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in_checker.h"

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

int				check_file(char *file, t_bool *b)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
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

char			*read_file(char *str)
{
	int			fd;
	int			ret;
	char		buff[4096];
	t_dstring	*file;

	file = NULL;
	fd = open(str, O_RDONLY);
	if (fd != -1)
	{
		while ((ret = read(fd, buff, 4095)))
		{
			buff[ret] = '\0';
			if (!file)
			{
				if (!(file = create_dstring(4096, buff)))
					return (NULL);
			}
			else if (!(file = push_str(file, buff)))
				return (NULL);
		}
	}
	close(fd);
	return (file->str);
}

// int				main(int argc, char **argv)
// {
// 	char		*file;
// 	char		*graph;
// 	t_bool		*b;

// 	if (!(b = init_struct()))
// 		return (0);
// 	if (argc != 2)
// 	{
// 		write(1, "Not enough arguments\n", 21);
// 		return (0);
// 	}
// 	if (!(file = read_file(argv[1])))
// 		return (0);
// 	if (!(graph = ft_strsub(file, 0, check_file(file, b))))
// 		return (0);
// 	printf("%s", graph);
// 	return (1);
// }
