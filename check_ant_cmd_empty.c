/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ant_cmd_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:42:59 by sadahan           #+#    #+#             */
/*   Updated: 2019/11/12 17:54:58 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_checker.h"

int			check_ant_number(char *file)
{
	int		i;

	i = 0;
	while (file[i] && file[i] != '\n')
	{
		if (!ft_isdigit(file[i]))
		{
			write(1, "Wrong number of ants\n", 21);
			return (0);
		}
		while (ft_isdigit(file[i]))
			i++;
	}
	return (i);
}

int			check_command(t_bool *b, char *file)
{
	int		i;
//  char cmd_tab[][] = {"##start", "##end"};
	char	*cmd;

	i = 0;
	while (file[i] != '\n' && file[i])
		i++;
	if (!(cmd = ft_strsub(file, 0, i)))
		return (0);
	if (!ft_strcmp(cmd, "##start"))
		b->start++;
	if (!ft_strcmp(cmd, "##end"))
		b->end++;
	if (b->start > 1 || b->end > 1)
		return (0);
	return (i);
}
