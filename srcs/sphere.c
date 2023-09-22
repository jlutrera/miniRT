#include "../include/miniRT.h"

double compute_lighting(t_scene scene, t_vec P, t_vec N, t_vec D, double s)
{
	t_vec	L;
	t_vec R;
	double	intensity;
	double	n_dot_l;
	double 	r_dot_v;

	intensity = scene.ambient.ratio;
	L = vec_sub(vec(scene.light.position.x, scene.light.position.y, scene.light.position.z), P);
	//Diffuse light
	n_dot_l = vec_dot(N, L);
	if (n_dot_l > 0)
		intensity += scene.light.bright * n_dot_l / (vec_length(N) * vec_length(L));
	//Specular light
	if (s > 0)
	{
		R = vec_sub(vec_mul(N, 2 * vec_dot(N, L)), L);
		r_dot_v = vec_dot(R, D);
		if (r_dot_v > 0)
			intensity += scene.light.bright * pow(r_dot_v / (vec_length(R) * vec_length(D)), s);
	}
	return (intensity);
}

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
	t_vec 		P;
	t_vec 		N;
	double 		i;

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
	{
		P = vec_add(vec(origin.x, origin.y, origin.z), vec_mul(direction, t_closest));
		N = vec_sub(vec(P.x, P.y, P.z), vec(closest_sphere->center.x, closest_sphere->center.y, closest_sphere->center.z));
		N = vec_unit(N);
		i = compute_lighting(scene, P, N, vec_mul(direction, -1), 300);
		return (t_point3){closest_sphere->color.r * i, closest_sphere->color.g * i, closest_sphere->color.b * i};
	}
	return (t_point3){0, 0, 0};
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}


void	process_img(t_data *data, t_scene *scene)
{
	t_point3	viewp_point;
	t_vec		d;
	t_point3	pixel_color;

	//Camera.
	//calculo el ancho y alto del viewport
	scene->camera.viewp.x = 2 * tan((scene->camera.fov * M_PI) / 360);
	scene->camera.viewp.y = data->image.height * scene->camera.viewp.x / data->image.width;
	scene->camera.viewp.z = 1;  //por conveniencia

	//Render
	for (int y = -data->image.height / 2; y <= data->image.height / 2; ++y)
	{
		for (int x = -data->image.width / 2; x <= data->image.width / 2; ++x)
		{
			viewp_point = (t_point3){x * scene->camera.viewp.x / data->image.width, y * scene->camera.viewp.y / data->image.height, scene->camera.viewp.z};
			d = vec_sub(vec(viewp_point.x, viewp_point.y, viewp_point.z), vec(scene->camera.position.x, scene->camera.position.y, scene->camera.position.z));
			pixel_color = trace_ray(scene->camera.position, d, *scene);
			my_mlx_pixel_put(data, data->image.width / 2 + x, data->image.height / 2 - y, write_color(pixel_color));
		}
	}
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->image.img, 0, 0);
}