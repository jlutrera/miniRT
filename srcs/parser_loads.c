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

#include "../include/miniRT.h"

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
	if (camera->fov < 0 || camera->fov > 180)
		return (FOV_E);
	if (ft_get_vector(s[2], &camera->direction) == -1)
		return (BAD_COORDINATES_E);
	if (!is_normalized(camera->direction))
		return (NORM_VECTOR_E);
	return (SUCCESS);
}

int	ft_load_light(t_light *light, char **s)
{
	if (light->declared)
		return (MORE_THAN_ONE_LIGHT_E);
	if (check_comps(s, 4))
		return (NUM_COMPONENTS_E);
	light->declared = true;
	if (ft_get_point(s[1], &light->position) == -1)
		return (BAD_COORDINATES_E);
	light->bright = ft_atod(s[2]);
	if (light->bright < 0 || light->bright > 1)
		return (BAD_BRIGHT_E);
	if (ft_get_color(s[3], &light->color) == -1)
		return (COLOUR_E);
	return (SUCCESS);
}
