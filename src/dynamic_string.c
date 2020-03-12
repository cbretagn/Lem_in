/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:03:21 by cbretagn          #+#    #+#             */
/*   Updated: 2020/03/12 18:23:10 by sadahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_dstring			*create_dstring(unsigned int cap, char *str)
{
	t_dstring		*ret;
	unsigned int	len;

	if (!(ret = (t_dstring *)malloc(sizeof(t_dstring))))
		exit_malloc(-2);
	len = ft_strlen(str);
	ret->capacity = cap;
	ret->size = len;
	if (!(ret->str = ft_strnew(ret->capacity)))
		exit_malloc(-2);
	if (str[0] != '\0')
		ft_strcpy(ret->str, str);
	return (ret);
}

void				delete_dstring(t_dstring *del)
{
	ft_strdel(&del->str);
	free(del);
	del = NULL;
}

t_dstring			*push_str(t_dstring *dest, char *src)
{
	t_dstring		*temp;
	int				new_cap;
	unsigned int	len;

	len = ft_strlen(src);
	temp = dest;
	if (len < temp->capacity - temp->size)
		ft_strcpy((temp->str + temp->size), src);
	else
	{
		temp = NULL;
		new_cap = dest->capacity;
		while (len >= new_cap - dest->size)
			new_cap *= 2;
		if (!(temp = create_dstring(new_cap, dest->str)))
			return (NULL);
		delete_dstring(dest);
		ft_strcpy((temp->str + temp->size), src);
	}
	temp->size += len;
	return (temp);
}

t_dstring			*push_str_nchar(t_dstring *dest, char *src, int n)
{
	t_dstring		*temp;
	int				new_cap;
	unsigned int	len;

	len = n + 1;
	temp = dest;
	if (len < temp->capacity)
		ft_strncpy((temp->str), src, n);
	else
	{
		temp = NULL;
		new_cap = dest->capacity;
		while ((int)len >= new_cap)
			new_cap *= 2;
		if (!(temp = create_dstring(new_cap, dest->str)))
			return (NULL);
		delete_dstring(dest);
		ft_strncpy((temp->str), src, n);
	}
	temp->str[temp->size + n] = '\0';
	temp->size += len;
	return (temp);
}
