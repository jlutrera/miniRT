/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:20:00 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 19:41:40 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length
			+ x * (data->image.bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

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
			return (compute_sphere_light(closest_obj->object, scene, p, ray));
		else if (closest_obj->type == PLANE)
			return (compute_plane_light(closest_obj->object, scene, p, ray));
		else
			return (compute_cylinder_light(closest_obj->object, scene, p, ray));
	}
	return ((t_point3){0, 0, 0});
}

static t_vec	init_viewport(t_point p, t_camera camera, t_image image)
{
	return (vec(p.x * camera.viewp.x / image.width,
			p.y * camera.viewp.y / image.height,
			camera.viewp.z));
}

void	process_img(t_data *data, t_scene *scene)
{
	t_vec		viewp_point;
	t_vec		d;
	t_point3	pixel_color;
	t_point		p;

	scene->camera.viewp.x = 2 * tan((scene->camera.fov * M_PI) / 360);
	scene->camera.viewp.y = data->image.height * scene->camera.viewp.x
		/ data->image.width;
	scene->camera.viewp.z = 0.75;
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
