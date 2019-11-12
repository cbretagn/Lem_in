/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:00:58 by cbretagn          #+#    #+#             */
/*   Updated: 2019/11/12 17:56:09 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_H
# define DYNAMIC_H

# define BUFFER_SIZE 1000

typedef struct		s_dstring
{
	unsigned int	size;
	unsigned int	capacity;
	char			*str;
}					t_dstring;

t_dstring			*create_dstring(unsigned int cap, char *str);
t_dstring			*push_str(t_dstring *dest, char *src);
t_dstring			*push_str(t_dstring *dest, char *src, int n);
void				delete_dstring(t_dstring *del);

#endif
