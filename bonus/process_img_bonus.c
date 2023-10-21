/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:20:00 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/21 11:25:24 by jutrera-         ###   ########.fr       */
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

static t_camera	*init_cam(t_data *data, t_scene *scene)
{
	t_camera	*cam;

	cam = scene->camera;
	while (!cam->active)
		cam = cam->next;
	cam->viewp.z = 0.75;
	cam->viewp.x = 2 * tan((cam->fov * M_PI) / 360);
	cam->viewp.y = data->image.height * cam->viewp.x
		/ data->image.width;
	return (cam);
}

void	process_img(t_data *data, t_scene *scene)
{
	t_vec		viewp_point;
	t_vec		d;
	t_point3	pixel_color;
	t_point		p;
	t_camera	*cam;

	cam = init_cam(data, scene);
	p.y = -data->image.height / 2 - 1;
	while (++p.y < data->image.height / 2)
	{
		p.x = -data->image.width / 2 - 1;
		while (++p.x < data->image.width / 2)
		{
			viewp_point = vec(p.x * cam->viewp.x / data->image.width,
					p.y * cam->viewp.y / data->image.height,
					cam->viewp.z);
			d = vec_rotate(viewp_point, cam->direction);
			pixel_color = trace_ray((t_ray){cam->position, d}, *scene);
			my_mlx_pixel_put(data, data->image.width / 2 + p.x,
				data->image.height / 2 - p.y, write_color(pixel_color));
		}
	}
	mlx_put_image_to_window(data->vars.mlx, data->vars.win,
		data->image.img, 0, 0);
}
