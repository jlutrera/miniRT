/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:48:22 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 18:51:05 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

int	ft_load_ambient(t_ambient *ambient, char **s)
{
	if (ambient->declared)
		return (MORE_THAN_ONE_AMBIENT_E);
	if (check_comps(s, 3))
		return (NUM_COMPONENTS_E);
	ambient->declared = true;
	ambient->ratio = ft_atod(s[1]);
	if (ambient->ratio < 0 || ambient->ratio > 1)
		return (RATIO_E);
	if (ft_get_color(s[2], &ambient->color) == -1)
		return (COLOUR_E);
	return (SUCCESS);
}

int	ft_load_camera(t_camera *camera, char **s)
{
	if (camera->declared)
		return (MORE_THAN_ONE_CAMERA_E);
	if (check_comps(s, 4))
		return (NUM_COMPONENTS_E);
	camera->declared = true;
	if (ft_get_point(s[1], &camera->position) == -1)
		return (BAD_COORDINATES_E);
	camera->fov = ft_atoi(s[3]);
	if (camera->fov <= 0 || camera->fov >= 180)
		return (FOV_E);
	if (ft_get_vector(s[2], &camera->direction) == -1)
		return (BAD_COORDINATES_E);
	if (!is_normalized(camera->direction))
		return (NORM_VECTOR_E);
	return (SUCCESS);
}

t_light	*new_light(char **s, int *e)
{
	t_light	*new_l;

	new_l = ft_calloc(sizeof(t_light), 1);
	if (!new_l)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	if (ft_get_point(s[1], &new_l->position) == -1)
		*e = BAD_COORDINATES_E;
	new_l->bright = ft_atod(s[2]);
	if (new_l->bright < 0 || new_l->bright > 1)
		*e = BAD_BRIGHT_E;
	if (ft_get_color(s[3], &new_l->color) == -1)
		*e = COLOUR_E;
	new_l->next = NULL;
	if (*e == SUCCESS)
		return (new_l);
	return (free(new_l), NULL);
}

int	ft_load_light(t_light **light, char **s)
{
	int		e;
	t_light	*new_l;
	t_light	*aux;

	if (check_comps(s, 4))
		return (NUM_COMPONENTS_E);
	new_l = new_light(s, &e);
	if (!new_l)
		return (e);
	if (!light || !*light)
		return (*light = new_l, SUCCESS);
	aux = *light;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new_l;
	return (SUCCESS);
}
