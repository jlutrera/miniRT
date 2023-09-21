#include "../include/miniRT.h"

void	intersect_sphere(t_point3 origin, t_vec direction, t_sphere *sp, t_point *t)
{
	t_vec 	co;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	co = vec_sub(vec(origin.x, origin.y, origin.z), vec(sp->center.x, sp->center.y, sp->center.z));
	a = vec_dot(direction, direction);
	b = 2 * vec_dot(co, direction);
	c = vec_dot(co, co) - sp->radius * sp->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		t->x = INFINITY;
		t->y = INFINITY;
	}
	else
	{
		t->x = (-b + sqrt(discriminant)) / (2 * a);
		t->y = (-b - sqrt(discriminant)) / (2 * a);
	}
}

t_point3	trace_ray(t_point3 origin, t_vec direction, t_scene scene)
{
	t_point		t;
	t_lst_obj	*sp;
	t_sphere	*closest_sphere;
	double		t_closest;

	t_closest = INFINITY;
	sp = scene.obj;
	closest_sphere = NULL;
	while (sp)
	{
		if (sp->type == SPHERE)
		{
			intersect_sphere(origin, direction, (t_sphere *)sp->object, &t);
			if (t.x > 1.0  && t.x < t_closest)
			{
				t_closest = t.x;
				closest_sphere = (t_sphere *)sp->object;
			}
			if (t.y > 1.0  && t.y < t_closest)
			{
				t_closest = t.y;
				closest_sphere = (t_sphere *)sp->object;
			}
		}
		sp = sp->next;
	}
	if (closest_sphere)
		return (t_point3){closest_sphere->color.r, closest_sphere->color.g, closest_sphere->color.b};
	return (t_point3){0, 0, 0};
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

void init_mlx(t_data *data)
{
	data->image.width = WIDTH;

	//Calculo la altura de la ventana en base al aspect ratio
	data->image.height = (int)(data->image.width / (ASPECT_RATIO));
	if (data->image.height < 1)
		data->image.height = 1;
	//Se crea la ventana (screen)
	data->vars.mlx = mlx_init();
	data->vars.win = mlx_new_window(data->vars.mlx, data->image.width , data->image.height, "miniRT");
	data->image.img = mlx_new_image(data->vars.mlx, data->image.width , data->image.height);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bits_per_pixel, &data->image.line_length, &data->image.endian);
}

void	process_img(t_scene scene)
{
	t_data		data;
	t_camera	camera;
	t_point3	viewp_point;
	t_vec		d;
	t_point3	pixel_color;

	init_mlx(&data);
	(void)scene;
	//Camera.
		//estos datos se cargan de scene, de momento me los invento
	camera.direction = (t_vec){0, 0, 1};
	camera.position = (t_point3){0, 0, 0};
	camera.fov = 90;
		//calculo el ancho y alto del viewport
	camera.viewp.x = 2 * tan(camera.fov / 2 * M_PI / 180);
	camera.viewp.y = data.image.height * camera.viewp.x / data.image.width;
	camera.viewp.z = 1;

	//Render
	for (int y = -data.image.height / 2; y <= data.image.height/2; ++y)
	{
		for (int x = -data.image.width / 2; x <= data.image.width / 2; ++x)
		{
			viewp_point = (t_point3){x * camera.viewp.x / data.image.width, y * camera.viewp.y / data.image.height, camera.viewp.z};
			d = vec_sub(vec(viewp_point.x, viewp_point.y, viewp_point.z), vec(camera.position.x, camera.position.y, camera.position.z));
			pixel_color = trace_ray(camera.position, d, scene);
			my_mlx_pixel_put(&data, data.image.width / 2 + x, data.image.height/2 - y, write_color(pixel_color));
		}
	}
	mlx_put_image_to_window(data.vars.mlx, data.vars.win, data.image.img, 0, 0);
	my_hooks(&data);
	mlx_loop(data.vars.mlx);
}