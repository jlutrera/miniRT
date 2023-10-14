/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:46:44 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 18:47:51 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

t_lst_obj	*ft_init_obj(void *object, t_obj_type type, double last_dist)
{
	t_lst_obj	*new_obj;

	new_obj = (t_lst_obj *) malloc(sizeof(t_lst_obj) * 1);
	if (!new_obj)
		return (NULL);
	if (type == SPHERE)
		new_obj->object = (t_sphere *) object;
	else if (type == PLANE)
		new_obj->object = (t_plane *) object;
	else if (type == CYLINDER)
		new_obj->object = (t_cylinder *) object;
	else
		new_obj->object = (t_triangle *) object;
	new_obj->type = type;
	new_obj->last_dist = last_dist;
	new_obj->skip = 0;
	new_obj->next = NULL;
	return (new_obj);
}

t_lst_obj	*ft_obj_last(t_lst_obj *obj)
{
	t_lst_obj	*aux;

	aux = obj;
	if (!aux)
		return (NULL);
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	ft_add_back_obj(t_lst_obj **obj, void **object, t_obj_type type,
		double last_dist)
{
	t_lst_obj	*new_obj;
	t_lst_obj	*aux;

	new_obj = ft_init_obj(*object, type, last_dist);
	if (!new_obj)
		return ;
	if (!(*obj))
	{
		*obj = new_obj;
		return ;
	}
	aux = ft_obj_last(*obj);
	if (!aux)
		*obj = new_obj;
	else
		aux->next = new_obj;
}
