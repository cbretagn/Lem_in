/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:00:58 by cbretagn          #+#    #+#             */
/*   Updated: 2020/02/25 17:04:54 by cbretagn         ###   ########.fr       */
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
t_dstring			*push_str_nchar(t_dstring *dest, char *src, int n);
void				delete_dstring(t_dstring *del);

#endif
