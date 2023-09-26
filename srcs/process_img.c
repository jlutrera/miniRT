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
	if (n_dot_l > EPSILON)
		intensity += scene.light.bright * n_dot_l / (vec_length(N) * vec_length(L));
	//Specular light
	if (s > 0)
	{
		R = vec_sub(vec_mul(N, 2 * vec_dot(N, L)), L);
		r_dot_v = vec_dot(R, D);
		if (r_dot_v > EPSILON)
			intensity += scene.light.bright * pow(r_dot_v / (vec_length(R) * vec_length(D)), s);
	}
	return (intensity);
}

void	intersect_sphere(t_ray ray, t_sphere *sp, t_point *t)
{
	t_vec 	co;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	co = vec_sub(vec(ray.origin.x, ray.origin.y, ray.origin.z), vec(sp->center.x, sp->center.y, sp->center.z));
	a = vec_dot(ray.dir, ray.dir);
	b = 2 * vec_dot(co, ray.dir);
	c = vec_dot(co, co) - sp->radius * sp->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		*t = (t_point){INFINITY, INFINITY};
	else
		*t = (t_point){(-b + sqrt(discriminant)) / (2 * a), (-b - sqrt(discriminant)) / (2 * a)};
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
    if (fabs(denom) < EPSILON)
        *t = (t_point){INFINITY, INFINITY};
	else
		*t = (t_point){vec_dot(plane->direction, OP) / denom, vec_dot(plane->direction, OP) / denom};
}
/*
void intersect_cylinder(t_ray ray, t_cylinder *cy, t_point *t)
{

}
*/
void	get_closest(t_ray ray, t_lst_obj *obj, t_lst_obj **closest_obj, double *t_closest)
{
	t_lst_obj	*tmp;
	t_point		t;

	while (obj)
	{
		if (obj->type == SPHERE)
			intersect_sphere(ray, (t_sphere *)obj->object, &t);
		else if (obj->type == PLANE)
			intersect_plane(ray, (t_plane *)obj->object, &t);
		//else
		//   intersect_cylinder(ray, (t_cylinder *)obj->object, &t);
		tmp = *closest_obj;
		if ((t.x > 1.0  && t.x < *t_closest) || (t.y > 1.0  && t.y < *t_closest))
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

t_point3	compute_sphere_light(t_sphere *sp, t_scene scene, t_vec P, t_ray ray)
{
	t_vec 		N;
	double 		i;

	N = vec_unit(vec_sub(P, vec(sp->center.x, sp->center.y, sp->center.z)));
	i = compute_lighting(scene, P, N, vec_mul(ray.dir, -1), 300);
	return (t_point3){sp->color.r * i, sp->color.g * i, sp->color.b * i};
}

t_point3	compute_plane_light(t_plane *pl, t_scene scene, t_vec P, t_ray ray)
{
	t_vec 		N;
	double 		i;

	N = vec_unit(pl->direction);
	i = compute_lighting(scene, P, N, vec_mul(ray.dir, -1), 300);
	return (t_point3){pl->color.r * i, pl->color.g * i, pl->color.b * i};
}
/*
t_point3	compute_cylinder_light(t_cylinder *cy, t_scene scene, t_vec P, t_ray ray)
{
	t_vec 		N;
	double 		i;

	N = vec_unit(cy->direction);
	i = compute_lighting(scene, P, N, vec_mul(ray.dir, -1), 300);
	return (t_point3){cy->color.r * i, cy->color.g * i, cy->color.b * i};
}
*/
t_point3	trace_ray(t_ray ray, t_scene scene)
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
	//	else
	//	return compute_cylinder_light(closest_obj->object, scene, P, ray);
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
	t_vec	a;
	t_vec	b;

	d = vec_unit(d);
	if (d.x != 0 || d.y != 0)
		a = vec_unit(vec_cross((t_vec){0, 0, 1}, d));
    else
 		a = vec_unit(vec_cross((t_vec){0, 1, 0}, d));
	b = vec_unit(vec_cross(a, d));
	double R[3][3] = {{-a.x,  -b.x, d.x}, { a.y, -b.y, d.y}, { a.z,  b.z, d.z}};
	return matrix_mul(R, v);
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
			viewp_point = vec(x * scene->camera.viewp.x / data->image.width, y * scene->camera.viewp.y / data->image.height, scene->camera.viewp.z);
			d = rotate_vec(viewp_point, scene->camera.direction);
			pixel_color = trace_ray((t_ray){scene->camera.position, d}, *scene);
			my_mlx_pixel_put(data, data->image.width / 2 + x, data->image.height / 2 - y, write_color(pixel_color));
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(data->vars.mlx, data->vars.win, data->image.img, 0, 0);
}