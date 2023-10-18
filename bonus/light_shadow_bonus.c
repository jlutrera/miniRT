/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:12:17 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/17 15:56:21 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static t_point3	calc_int(t_point3 p, double d, t_color c)
{
	t_point3	i;

	i.x = p.x + d * c.r / 255;
	i.y = p.y + d * c.g / 255;
	i.z = p.z + d * c.b / 255;
	return (i);
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
		else
			intersect_tr(ray, (t_triangle *)obj->object, &t);
		if ((t.x > EPSILON && t.x < 100) || (t.y > EPSILON && t.y < 100))
			return (true);
		obj = obj->next;
	}
	return (false);
}

/**
 * @brief Compute the intensity of light at a point based on its normal and the light direction.
 * 
 * This function calculates the intensity of light at a point on a surface based on
 * the direction of the light, the normal at the point, and the properties of the light.
 * It considers both diffuse and specular lighting effects.
 * 
 * @param n Normal vector at the point.
 * @param l Direction vector from the point to the light source.
 * @param light Pointer to the light structure.
 * @param camera The camera structure containing its direction.
 * 
 * @return The computed intensity of light at the point.
 */

static t_point3	compute_int(t_vec n, t_vec l, t_light *light, t_camera camera)
{
	double		dot_v;
	t_vec		r;
	t_point3	intensity;
	double		coef;

	intensity = (t_point3){0, 0, 0};
	dot_v = vec_dot(n, l) * light->bright;
	if (dot_v > EPSILON)
		intensity = calc_int(intensity, dot_v, light->color);
	r = vec_sub(vec_mul(n, 2 * vec_dot(n, l)), l);
	dot_v = vec_dot(r, vec_mul(camera.direction, -1));
	if (dot_v > EPSILON)
	{
		coef = light->bright * pow(dot_v / (vec_length(r)
					* vec_length(camera.direction)), SPECULAR);
		intensity = calc_int(intensity, coef, light->color);
	}
	return (intensity);
}

/**
 * @brief Compute the shadow intensity at a point.
 * 
 * This function calculates the shadow intensity at a point on a surface based on
 * the lighting conditions in the scene. It checks if the point is in shadow for 
 * each light source in the scene and accumulates the shadow intensity.
 * 
 * @param scene The scene containing lighting and other information.
 * @param p The point on the surface for which the shadow intensity is to be computed.
 * @param n Normal vector at the point.
 * 
 * @return The computed shadow intensity at the point.
 */

t_point3	compute_shadows(t_scene scene, t_vec p, t_vec n)
{
	t_vec		l;
	t_point3	intensity;
	t_point3	tmp;
	t_light		*light;

	intensity = (t_point3){0, 0, 0};
	light = scene.light;
	while (light)
	{
		l = vec_unit(vec_sub(point_to_vec(light->position), p));
		if (get_closest_shadow((t_ray){vec_to_point(p), l}, scene.obj))
		{
			tmp = compute_int(n, l, light, scene.camera);
			intensity.x += tmp.x;
			intensity.y += tmp.y;
			intensity.z += tmp.z;
		}
		light = light->next;
	}
	return (intensity);
}

/**
 * @brief Compute the color lighting at a point.
 * 
 * This function calculates the color lighting at a point on a surface based on
 * the lighting conditions in the scene. It considers the effects of each light 
 * source in the scene on the point.
 * 
 * @param scene The scene containing lighting and other information.
 * @param p The point on the surface for which the color lighting is to be computed.
 * @param n Normal vector at the point.
 * 
 * @return The computed color lighting at the point.
 */

t_point3	compute_colour_lighting(t_scene scene, t_vec p, t_vec n)
{
	t_vec		l;
	t_point3	intensity;
	t_point3	tmp;
	t_light		*light;

	intensity = (t_point3){0, 0, 0};
	light = scene.light;
	while (light)
	{
		l = vec_unit(vec_sub(point_to_vec(light->position), p));
		tmp = compute_int(n, l, light, scene.camera);
		intensity.x += tmp.x;
		intensity.y += tmp.y;
		intensity.z += tmp.z;
		light = light->next;
	}
	return (intensity);
}
