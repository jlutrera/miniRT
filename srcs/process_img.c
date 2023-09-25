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

void intersect_plane(t_ray ray, t_plane *plane, t_point *t)
{
    t_vec	plane_vec;
    t_vec	OP;
	t_vec	plane_origin;
    double	denom;

	denom = vec_dot(plane->direction, ray.dir);
    plane_vec = vec(plane->coordinate.x, plane->coordinate.y, plane->coordinate.z);
	plane_origin = vec(ray.origin.x, ray.origin.y, ray.origin.z);
	OP = vec_sub(plane_vec, plane_origin);
    if (fabs(denom) < 1e-6)
        t->x = INFINITY;
	else
		t->x = vec_dot(plane->direction, OP) / denom;
}

t_point3	trace_ray(t_point3 origin, t_vec direction, t_scene scene)
{
	t_point		t;
	t_lst_obj	*obj;
	t_lst_obj	*closest_obj;
	double		t_closest;
	t_vec 		P;
	t_vec 		N;
	double 		i;
	t_sphere	*sp;
	t_plane		*pl;
	//t_cylinder	*cy;

	t_closest = INFINITY;
	obj = scene.obj;
	closest_obj = NULL;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			intersect_sphere(origin, direction, (t_sphere *)obj->object, &t);
			if (t.x > 1.0  && t.x < INFINITY && t.x < t_closest)
			{
				t_closest = t.x;
				closest_obj = obj;
			}
			if (t.y > 1.0  && t.y < t_closest)
			{
				t_closest = t.y;
				closest_obj = obj;
			}
		}
		else if (obj->type == PLANE)
		{
			intersect_plane((t_ray){origin, direction}, (t_plane *)obj->object, &t);
			if (t.x > 1.0 && t.x < INFINITY && t.x < t_closest)
			{
				t_closest = t.x;	
				closest_obj = obj;
			}
		}
		else if (obj->type == CYLINDER)
		{
			// printf("intersect_cylinder()\n");
		}
		obj = obj->next;
	}
	if (closest_obj)
	{
		if (closest_obj->type == SPHERE)
		{
			sp = (t_sphere *)(closest_obj->object);
			P = vec_add(vec(origin.x, origin.y, origin.z), vec_mul(direction, t_closest));
			N = vec_sub(P, vec(sp->center.x, sp->center.y, sp->center.z));
			N = vec_unit(N);
			i = compute_lighting(scene, P, N, vec_mul(direction, -1), 300);
			return (t_point3){sp->color.r * i, sp->color.g * i, sp->color.b * i};
		}
		else if (closest_obj->type == PLANE)
		{
			pl = (t_plane *)(closest_obj->object);
			i = 1;  //Hay que ajustar i a la luz reflejada por el plano
			return (t_point3){pl->color.r * i, pl->color.g * i, pl->color.b * i};
		}
		else if (closest_obj->type == CYLINDER)
		{
			printf("trace_ray() cylinder\n");
		}
	}
	return (t_point3){0, 0, 0};
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char	*dst;

	dst = data->image.addr + (y * data->image.line_length + x * (data->image.bits_per_pixel / 8));
	*(unsigned int*)dst = colour;
}

t_vec matrix_mul(double mat[3][3], t_vec v) {
	return (t_vec) {
		.x = mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z,
		.y = mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z,
		.z = mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z
	};
}

t_vec rotate_vec(t_vec v, t_vec d)
{
	// Normalizar el vector director
	d = vec_unit(d);

	t_vec	a = {0, 0, 0};
	// Escoger un vector a que no sea paralelo a d
	if (d.x != 0 || d.y != 0)
	{
		a = vec_unit(vec_cross(d, (t_vec){0, 0, 1}));
	} 
    else
	{
 		a = vec_unit(vec_cross(d, (t_vec){0, 1, 0}));
	}
	// Calcular los vectores base
	t_vec x = vec_unit(vec_cross(a, d));
	t_vec y = vec_cross(d, x);

	// Construir la matriz de rotación
	double R[3][3] =
	{
		{x.x, y.x, d.x},
		{x.y, y.y, d.y},
		{x.z, y.z, d.z}
	};
	// Multiplicar la matriz de rotación por el vector v
	return matrix_mul(R, v);
}


void	process_img(t_data *data, t_scene *scene)
{
	t_vec	viewp_point;
	t_vec		d;
	t_point3	pixel_color;

	//Camera.
	//calculo el ancho y alto del viewport
	scene->camera.viewp.x = 2 * tan((scene->camera.fov * M_PI) / 360);
	scene->camera.viewp.y = data->image.height * scene->camera.viewp.x / data->image.width;
	scene->camera.viewp.z = 1;

	//Render
	for (int x = -data->image.height / 2; x <= data->image.height / 2; ++x)
	{
		for (int y = -data->image.width / 2; y <= data->image.width / 2; ++y)
		{
			viewp_point = (t_vec){x * scene->camera.viewp.x / data->image.width, y * scene->camera.viewp.y / data->image.height, scene->camera.viewp.z};
			d = rotate_vec(viewp_point, scene->camera.direction);
			pixel_color = trace_ray(scene->camera.position, vec_unit(d), *scene);
			my_mlx_pixel_put(data, data->image.width / 2 + y, data->image.height / 2 - x, write_color(pixel_color));
		}
	}
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->image.img, 0, 0);
}

			// d = vec_sub(vec(viewp_point.x, viewp_point.y, viewp_point.z), vec(scene->camera.position.x, scene->camera.position.y, scene->camera.position.z));
