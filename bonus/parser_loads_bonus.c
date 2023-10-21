/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loads_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:48:22 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/21 11:18:19 by jutrera-         ###   ########.fr       */
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

t_camera	*new_camera(char **s, int *e)
{
	t_camera	*new_c;

	new_c = ft_calloc(sizeof(t_camera), 1);
	if (!new_c)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	if (ft_get_point(s[1], &new_c->position) == -1)
		*e = BAD_COORDINATES_E;
	new_c->fov = ft_atoi(s[3]);
	if (new_c->fov <= 0 || new_c->fov >= 180)
		*e = FOV_E;
	if (ft_get_vector(s[2], &new_c->direction) == -1)
		*e = BAD_COORDINATES_E;
	if (!is_normalized(new_c->direction))
		*e = NORM_VECTOR_E;
	new_c->next = NULL;
	new_c->active = false;
	if (*e == SUCCESS)
		return (new_c);
	return (free(new_c), NULL);
}

int	ft_load_camera(t_camera **camera, char **s)
{
	int			e;
	t_camera	*new_c;
	t_camera	*aux;

	if (check_comps(s, 4))
		return (NUM_COMPONENTS_E);
	new_c = new_camera(s, &e);
	if (!new_c)
		return (e);
	if (!camera || !*camera)
	{
		new_c->active = true;
		return (*camera = new_c, SUCCESS);
	}
	aux = *camera;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new_c;
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
