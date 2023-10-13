/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:12:17 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 18:35:49 by jutrera-         ###   ########.fr       */
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
			intersect_sphere(ray, (t_sphere *)obj->object, &t);
		else if (obj->type == PLANE)
			intersect_plane(ray, (t_plane *)obj->object, &t);
		else if (obj->type == CYLINDER)
			intersect_cylinder(ray, (t_cylinder *)obj->object, &t);
		else
			intersect_triangle(ray, (t_triangle *)obj->object, &t);
		tmp = *closest_obj;
		if ((t.x > EPSILON && t.x < *t_closest) || (t.y > EPSILON
				&& t.y < *t_closest))
		{
			tmp = obj;
			if (t.y < *t_closest)
				*t_closest = t.y;
			else
				*t_closest = t.x;
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
			intersect_sphere(ray, (t_sphere *)obj->object, &t);
		else if (obj->type == PLANE)
			intersect_plane(ray, (t_plane *)obj->object, &t);
		else if (obj->type == CYLINDER)
			intersect_cylinder(ray, (t_cylinder *)obj->object, &t);
		else
			intersect_triangle(ray, (t_triangle *)obj->object, &t);
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
	t_light		*light;

	intensity = 0;
	light = scene.light;
	while (light)
	{
		l = vec_unit(vec_sub(point_to_vec(light->position), p));
		if (get_closest_shadow((t_ray){vec_to_point(p), l}, scene.obj))
		{
			dot_v = vec_dot(n, l);
			if (dot_v > EPSILON)
				intensity += light->bright * dot_v;
		}
		light = light->next;
	}
	return (intensity);
}

t_point3	calc_int(t_point3 p, double d, t_color c)
{
	t_point3	i;

	i.x = p.x + d * c.r;
	i.y = p.y + d * c.g;
	i.z = p.z + d * c.b;
	return (i);
}

t_point3	compute_colour_lighting(t_scene scene, t_vec p, t_vec n)
{
	t_vec		l;
	t_point3	intensity;
	double		dot_v;
	t_light		*light;

	intensity = (t_point3){0, 0, 0};
	light = scene.light;
	while (light)
	{
		l = vec_unit(vec_sub(point_to_vec(light->position), p));
		dot_v = vec_dot(n, l) * light->bright / 255;
		if (dot_v > EPSILON)
			intensity = calc_int(intensity, dot_v, light->color);
		light = light->next;
	}
	return (intensity);
}
