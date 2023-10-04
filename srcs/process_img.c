#include "../include/miniRT.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

static t_point3	trace_ray(t_ray ray, t_scene scene)
{
	t_lst_obj	*closest_obj;
	double		t_closest;
	t_vec 		P;

	t_closest = INFINITY;
	closest_obj = NULL;
	get_closest(ray, scene.obj, &closest_obj, &t_closest);
	if (closest_obj)
	{
		P = vec_add(vec(ray.origin.x, ray.origin.y, ray.origin.z), vec_mul(ray.dir, t_closest));
		if (closest_obj->type == SPHERE)
			return compute_sphere_light(closest_obj->object, scene, P, ray);
		else if (closest_obj->type == PLANE)
			return compute_plane_light(closest_obj->object, scene, P, ray);
		else
			return compute_cylinder_light(closest_obj->object, scene, P, ray);
	}
	return (t_point3){0, 0, 0};
}

void	process_img(t_data *data, t_scene *scene)
{
	t_vec		viewp_point;
	t_vec		d;
	t_point3	pixel_color;
	int			x;
	int			y;

	scene->camera.viewp.x = 2 * tan((scene->camera.fov * M_PI) / 360);
	scene->camera.viewp.y = data->image.height * scene->camera.viewp.x / data->image.width;
	scene->camera.viewp.z = 1;
	y = -data->image.height / 2;
	while (y < data->image.height / 2)
	{
		x = -data->image.width / 2;
		while (x < data->image.width / 2)
		{
			viewp_point = vec(x * scene->camera.viewp.x / data->image.width,
					y * scene->camera.viewp.y / data->image.height, scene->camera.viewp.z);
			d = vec_rotate(viewp_point, scene->camera.direction);
			pixel_color = trace_ray((t_ray){scene->camera.position, d}, *scene);
			my_mlx_pixel_put(data, data->image.width / 2 + x, data->image.height / 2 - y, write_color(pixel_color));
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->image.img, 0, 0);
}