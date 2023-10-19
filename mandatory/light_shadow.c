/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:12:17 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/19 19:02:12 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	get_closest(t_ray ray, t_lst_obj *obj, t_lst_obj **closest_obj,
			double *t_closest)
{
	t_lst_obj	*tmp;
	t_point		t;

	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sp(ray, (t_sphere *)obj->object, &t);
		else if (obj->type == PLANE)
			intersect_pl(ray, (t_plane *)obj->object, &t);
		else if (obj->type == CYLINDER)
			intersect_cy(ray, (t_cylinder *)obj->object, &t);
		tmp = *closest_obj;
		if ((t.x > EPSILON && t.x < *t_closest) || (t.y > EPSILON
				&& t.y < *t_closest))
		{
			tmp = obj;
			*t_closest = fmin(fmin(t.x, t.y), *t_closest);
		}
		if (tmp != *closest_obj)
			*closest_obj = tmp;
		obj = obj->next;
	}
}

static bool	get_closest_shadow(t_ray ray, t_lst_obj *obj)
{
	t_point	t;

	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sp(ray, (t_sphere *)obj->object, &t);
		else if (obj->type == PLANE)
			intersect_pl(ray, (t_plane *)obj->object, &t);
		else if (obj->type == CYLINDER)
			intersect_cy(ray, (t_cylinder *)obj->object, &t);
		if ((t.x > EPSILON && t.x < 100) || (t.y > EPSILON && t.y < 100))
			return (true);
		obj = obj->next;
	}
	return (false);
}

double	compute_shadows(t_scene scene, t_vec p, t_vec n)
{
	t_vec		l;
	double		intensity;
	double		dot_v;

	intensity = 0;
	l = vec_unit(vec_sub(point_to_vec(scene.light.position), p));
	if (get_closest_shadow((t_ray){vec_to_point(p), l}, scene.obj))
	{
		dot_v = vec_dot(n, l);
		if (dot_v > EPSILON)
			intensity += scene.light.bright * dot_v;
	}
	return (intensity);
}

t_point3	compute_lighting(t_scene scene, t_vec p, t_vec n)
{
	t_vec		l;
	t_point3	intensity;
	double		dot_v;

	intensity = (t_point3){0, 0, 0};
	l = vec_unit(vec_sub(point_to_vec(scene.light.position), p));
	dot_v = vec_dot(n, l) * scene.light.bright;
	if (dot_v > EPSILON)
	{
		intensity.x += dot_v;
		intensity.y += dot_v;
		intensity.z += dot_v;
	}
	return (intensity);
}
