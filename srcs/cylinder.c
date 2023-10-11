/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:38:14 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/09 11:28:35 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_point3	compute_cylinder_colour_light(t_cylinder *cy, t_scene scene,
		t_vec p, t_ray ray)
{
	t_vec		n;
	t_point3	i;
	t_vec		op;
	t_point3	intensity;
	double		shadow;

	op = vec_sub(p, point_to_vec(cy->coordinate));
	shadow = vec_dot(op, cy->direction);
	if (fabs(shadow - cy->height) < EPSILON)
		n = vec_unit(cy->direction);
	else if (fabs(shadow) < EPSILON)
		n = vec_unit(vec_mul(cy->direction, -1));
	else
		n = vec_unit(vec_sub(op, vec_mul(vec_unit(cy->direction), shadow)));
	i = compute_colour_lighting(scene, p, n, vec_unit(vec_mul(ray.dir, -1)));
	shadow = compute_shadows(scene, p, n, vec_unit(vec_mul(ray.dir, -1)));
	intensity.x = i.x - shadow + scene.ambient.ratio
		* scene.ambient.color.r / 255 ;
	intensity.y = i.y - shadow + scene.ambient.ratio
		* scene.ambient.color.g / 255 ;
	intensity.z = i.z - shadow + scene.ambient.ratio
		* scene.ambient.color.b / 255;
	return ((t_point3){fmax(10, intensity.x * cy->color.r), fmax(10,
			intensity.y * cy->color.g), fmax(10, intensity.z * cy->color.b)});
}

int	ft_load_cylinders(t_lst_obj **obj, char **s)
{
	int			e;
	t_cylinder	*new_cy;

	if (check_comps(s, 6))
		return (NUM_COMPONENTS_E);
	new_cy = new_cylinder(s, &e);
	if (!new_cy)
		return (e);
	ft_add_back_obj(obj, (void **)&new_cy, CYLINDER, ft_get_dist());
	return (SUCCESS);
}

t_cylinder	*new_cylinder(char **s, int *e)
{
	t_cylinder	*new_cy;

	new_cy = ft_calloc(sizeof(t_cylinder), 1);
	if (!new_cy)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	new_cy->radius = ft_atod(s[3]) / 2;
	new_cy->height = ft_atod(s[4]);
	if (ft_get_point(s[1], &new_cy->coordinate) == -1
		|| ft_get_vector(s[2], &new_cy->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_cy->direction))
		*e = NORM_VECTOR_E;
	else if (new_cy->radius <= 0 || new_cy->height <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[5], &new_cy->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_cy);
	return (free(new_cy), NULL);
}
