/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:12:42 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/12 17:13:30 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "get_next_line.h"
# include "dynamic.h"
# include <unistd.h>
# include <stdlib.h>

int			hash_fun(char *str);
char		**put_in_table(char *str, char **tab, int size);
int			search_in_table(char *str, char **tab, int size);

#endif
