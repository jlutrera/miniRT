/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:12:17 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/17 15:47:51 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/**
 * @brief Determines the closest object that a ray intersects with.
 * 
 * This function iterates over all objects in the scene and checks for intersections
 * with the provided ray. It updates the closest object and the intersection distance
 * if a closer intersection is found.
 * 
 * @param ray The ray to check intersections for.
 * @param obj The list of objects in the scene.
 * @param closest_obj The closest intersected object (updated by the function).
 * @param t_closest The distance to the closest intersection (updated by the function).
 */

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

/**
 * @brief Checks if a ray intersects with any object in the scene within a certain distance.
 * 
 * This function is used to determine if a point is in shadow. It checks if there's any
 * object between the point and the light source.
 * 
 * @param ray The ray originating from the point and pointing towards the light.
 * @param obj The list of objects in the scene.
 * 
 * @return true if there's an intersection within the specified distance, false otherwise.
 */

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

/**
 * @brief Computes the shadow intensity at a pixel in the scene.
 * 
 * This function determines how much a pixel is in shadow based on the objects
 * between the point and the light source.
 * 
 * @param scene The scene containing objects, lights, etc.
 * @param p The pixel in the scene.
 * @param n The normal at the pixel.
 * 
 * @return The shadow intensity at the pixel.
 */

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

/**
 * @brief Computes the lighting intensity at a point in the scene.
 * 
 * This function determines the lighting contribution at a point based on the
 * angle between the surface normal and the direction to the light source.
 * 
 * @param scene The scene containing objects, lights, etc.
 * @param p The point in the scene.
 * @param n The normal at the point.
 * 
 * @return The lighting intensity at the point.
 */

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
