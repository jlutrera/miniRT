/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:38:14 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/08 13:38:14 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_point3	compute_cylinder_light(t_cylinder *cy, t_scene scene,
		t_vec p, t_ray ray)
{
	t_vec	n;
	double	i;
	double	h;
	t_vec	op;
	t_vec	proj;

	h = vec_dot(vec_sub(p, point_to_vec(cy->coordinate)), cy->direction);
	if (fabs(h - cy->height) < EPSILON || fabs(h) < EPSILON)
		n = vec_unit(cy->direction);
	else
	{
		op = vec_unit(vec_sub(p, point_to_vec(cy->coordinate)));
		proj = vec_mul(cy->direction, vec_dot(op, cy->direction));
		n = vec_unit(vec_sub(op, proj));
	}
	i = compute_lighting(scene, p, n, vec_unit(vec_mul(ray.dir, -1)));
	i -= compute_shadows(scene, p, n, ray);
	return ((t_point3){cy->color.r * i, cy->color.g * i, cy->color.b * i});
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

	new_cy = ft_calloc(sizeof(t_cylinder *), 1);
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
