/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:20:00 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/19 11:13:04 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static void	get_closest(t_ray ray, t_lst_obj *obj, t_lst_obj **closest_obj,
			double *t_closest)
{
	t_point		t;

	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sp(ray, (t_sphere *)obj->object, &t);
		else if (obj->type == PLANE)
			intersect_pl(ray, (t_plane *)obj->object, &t);
		else if (obj->type == CYLINDER)
			intersect_cy(ray, (t_cylinder *)obj->object, &t);
		else if (obj->type == TRIANGLE)
			intersect_tr(ray, (t_triangle *)obj->object, &t);
		else
			intersect_co(ray, (t_cone *)obj->object, &t);
		if ((t.x > EPSILON && t.x < *t_closest) || (t.y > EPSILON
				&& t.y < *t_closest))
		{
			*closest_obj = obj;
			*t_closest = fmin(fmin(t.x, t.y), *t_closest);
		}
		obj = obj->next;
	}
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	if (x >= 0 && x < data->image.width && y >= 0 && y < data->image.height)
	{
		dst = data->image.addr + (y * data->image.line_length
				+ x * (data->image.bits_per_pixel / 8));
		*(unsigned int *)dst = colour;
	}
}

/**
 * @brief Trace a ray through the scene to determine its color.
 * 
 * This function sends a ray into the scene and determines the color of the pixel
 * that the ray intersects based on the objects in the scene. It checks for intersections
 * with all objects and calculates the color based on the closest object it hits.
 * 
 * @param ray The ray being sent into the scene.
 * @param scene The scene containing objects, lights, and other relevant data.
 * 
 * @return The color of the pixel that the ray intersects.
 */

static t_point3	trace_ray(t_ray ray, t_scene scene)
{
	t_lst_obj	*closest_obj;
	double		t_closest;
	t_vec		p;

	t_closest = INFINITY;
	closest_obj = NULL;
	get_closest(ray, scene.obj, &closest_obj, &t_closest);
	if (closest_obj)
	{
		p = vec_add(point_to_vec(ray.origin), vec_mul(ray.dir, t_closest));
		if (closest_obj->type == SPHERE)
			return (compute_sp_colour_light(closest_obj->object, scene, p));
		else if (closest_obj->type == PLANE)
			return (compute_pl_colour_light(closest_obj->object, scene, p));
		else if (closest_obj->type == CYLINDER)
			return (compute_cy_colour_light(closest_obj->object, scene, p));
		else if (closest_obj->type == TRIANGLE)
			return (compute_tr_colour_light(closest_obj->object, scene, p));
		else
			return (compute_co_colour_light(closest_obj->object, scene, p));
	}
	return ((t_point3){0, 0, 0});
}

static t_vec	init_viewport(t_point p, t_camera camera, t_image image)
{
	return (vec(p.x * camera.viewp.x / image.width,
			p.y * camera.viewp.y / image.height,
			camera.viewp.z));
}

/**
 * @brief Process the image by tracing rays for each pixel.
 * 
 * This function processes the entire image by sending a ray through each pixel
 * and determining its color based on the scene's objects and lighting conditions.
 * It then draws the computed color to the corresponding pixel in the image.
 * 
 * @param data Pointer to the data structure containing image and other relevant data.
 * @param scene Pointer to the scene containing objects, lights, and other relevant data.
 */

void	process_img(t_data *data, t_scene *scene)
{
	t_vec		viewp_point;
	t_vec		d;
	t_point3	pixel_color;
	t_point		p;

	scene->camera.viewp.z = 0.75;
	scene->camera.viewp.x = 2 * tan((scene->camera.fov * M_PI) / 360);
	scene->camera.viewp.y = data->image.height * scene->camera.viewp.x
		/ data->image.width;
	p.y = -data->image.height / 2 - 1;
	while (++p.y < data->image.height / 2)
	{
		p.x = -data->image.width / 2 - 1;
		while (++p.x < data->image.width / 2)
		{
			viewp_point = init_viewport(p, scene->camera, data->image);
			d = vec_rotate(viewp_point, scene->camera.direction);
			pixel_color = trace_ray((t_ray){scene->camera.position, d}, *scene);
			my_mlx_pixel_put(data, data->image.width / 2 + p.x,
				data->image.height / 2 - p.y, write_color(pixel_color));
		}
	}
	mlx_put_image_to_window(data->vars.mlx, data->vars.win,
		data->image.img, 0, 0);
}
