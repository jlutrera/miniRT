/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:38:21 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/19 18:57:45 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

t_vec	calc_normal(t_cone *co, t_vec cp)
{
	t_vec	v;
	double	m;
	double	k;
	t_vec	n;

	v = vec_unit(vec_mul(co->direction, -1));
	m = co->radius * co->radius / (2 * co->height);
	k = 1 + pow(co->radius / co->height, 2);
	n = vec_unit(vec_sub(cp, vec_mul(v, m * k)));
	return (n);
}

t_point3	compute_co_colour_light(t_cone *co, t_scene scene, t_vec p)
{
	t_vec		n;
	t_point3	i;
	t_point3	intensity;
	t_point3	shadow;
	t_vec		cp;

	cp = vec_sub(p, point_to_vec(co->coordinate));
	if (fabs(vec_dot(cp, vec_unit(co->direction)) - co->height) < EPSILON)
		n = vec_unit(co->direction);
	else if (fabs(vec_dot(cp, co->direction)) < EPSILON)
		n = vec_mul(vec_unit(co->direction), -1);
	else
		n = calc_normal(co, cp);
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
