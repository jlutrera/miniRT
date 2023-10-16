/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:38:21 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/16 11:01:29 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static t_vec	compute_cone_normal(t_cone *co, t_vec p)
{
	t_vec	V;	
	t_vec	P_minus_V;
	double	height;
	t_vec	proj;
	t_vec	base;

	V = point_to_vec(co->coordinate);
	P_minus_V = vec_sub(p, V);
	height = vec_dot(P_minus_V, vec_unit(co->direction));
	proj = vec_mul(vec_unit(co->direction), height);
	base = vec_add(V, proj);
	height = co->radius / sin(atan(co->radius / co->height));
	return vec_unit(vec_mul(vec_unit(vec_sub(p, base)), height));
}

t_point3	compute_co_colour_light(t_cone *co, t_scene scene, t_vec p)
{
	t_vec		n;
	t_point3	i;
	t_vec		op;
	t_point3	intensity;
	t_point3	shadow;

	op = vec_sub(p, point_to_vec(co->coordinate));
	i.x = vec_dot(op, co->direction);
	i.y = cos(atan2(co->radius, co->height));
	n = compute_cone_normal(co, p);
	i = compute_colour_lighting(scene, p, n);
	shadow = compute_shadows(scene, p, n);
	intensity.x = i.x - shadow.x + scene.ambient.ratio
		* scene.ambient.color.r / 255 ;
	intensity.y = i.y - shadow.y + scene.ambient.ratio
		* scene.ambient.color.g / 255 ;
	intensity.z = i.z - shadow.z + scene.ambient.ratio
		* scene.ambient.color.b / 255;
	return ((t_point3){fmax(10, intensity.x * co->color.r), fmax(10,
			intensity.y * co->color.g), fmax(10, intensity.z * co->color.b)});
}

int	ft_load_co(t_lst_obj **obj, char **s)
{
	int		e;
	t_cone	*new_cone;

	if (check_comps(s, 6))
		return (NUM_COMPONENTS_E);
	new_cone = new_co(s, &e);
	if (!new_cone)
		return (e);
	ft_add_back_obj(obj, (void **)&new_cone, CONE, ft_get_dist());
	return (SUCCESS);
}

t_cone	*new_co(char **s, int *e)
{
	t_cone	*new_cone;

	new_cone = ft_calloc(sizeof(t_cone), 1);
	if (!new_cone)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	new_cone->radius = ft_atod(s[3]) / 2;
	new_cone->height = ft_atod(s[4]);
	if (ft_get_point(s[1], &new_cone->coordinate) == -1
		|| ft_get_vector(s[2], &new_cone->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_cone->direction))
		*e = NORM_VECTOR_E;
	else if (new_cone->radius <= 0 || new_cone->height <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[5], &new_cone->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_cone);
	return (free(new_cone), NULL);
}
