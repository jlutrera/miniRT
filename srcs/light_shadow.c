#include "../include/miniRT.h"

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
		else
			intersect_cylinder(ray, (t_cylinder *)obj->object, &t);
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

double compute_shadows(t_scene scene, t_vec P, t_vec N, t_vec D)
{
	t_vec		L;
	t_vec		R;
	double		intensity;
	double 		dot_v;
	t_lst_obj	*closest_obj;
	double		s;

	closest_obj = NULL;
	intensity = 0;
	s = 300;
	N = vec_unit(N);
	D = vec_unit(D);
	L = vec_unit(vec_sub(vec(scene.light.position.x, scene.light.position.y, scene.light.position.z), P));
	get_closest((t_ray){(t_point3){P.x, P.y, P.z}, vec_unit(L)}, scene.obj, &closest_obj, &(t_point){100, INFINITY}.x);
	if (closest_obj)
	{
		//Diffuse light
		dot_v = vec_dot(N, L);
		if (dot_v > EPSILON)
			intensity -= scene.light.bright * dot_v;
		//Specular light
		R = vec_unit(vec_sub(vec_mul(N, 2 * dot_v), L));
		dot_v = vec_dot(R, D);
		if (dot_v > EPSILON)
			intensity -= scene.light.bright * pow(dot_v, s);
	}
	return (intensity);
}

double compute_lighting(t_scene scene, t_vec P, t_vec N, t_vec D)
{
	t_vec		L;
	t_vec		R;
	double		intensity;
	double 		dot_v;
	double		s;

	s = 600;
	N = vec_unit(N);
	D = vec_unit(D);
	intensity = scene.ambient.ratio;
	L = vec_unit(vec_sub(vec(scene.light.position.x, scene.light.position.y, scene.light.position.z), P));
	//Diffuse light
	dot_v = vec_dot(N, L);
	if (dot_v > EPSILON)
		intensity += scene.light.bright * dot_v;
	//Specular light
	R = vec_unit(vec_sub(vec_mul(N, 2 * dot_v), L));
	dot_v = vec_dot(R, D);
	if (dot_v > EPSILON)
		intensity += scene.light.bright * pow(dot_v, s);
	return (intensity);
}

// double compute_shadows(t_scene scene, t_vec P, t_vec N, t_vec D)
// {
// 	t_vec		L;
// 	t_vec		R;
// 	double		intensity;
// 	double 		dot_v;
// 	t_lst_obj	*closest_obj;
// 	double		s;

// 	closest_obj = NULL;
// 	intensity = 0;
// 	s = 300;
// 	L = vec_unit(vec_sub(vec(scene.light.position.x, scene.light.position.y, scene.light.position.z), P));
// 	get_closest((t_ray){(t_point3){P.x, P.y, P.z}, vec_unit(L)}, scene.obj, &closest_obj, &(t_point){100, INFINITY}.x);
// 	if (closest_obj)
// 	{
// 		//Diffuse light
// 		dot_v = vec_dot(N, L);
// 		if (dot_v > EPSILON)
// 			intensity -= scene.light.bright * dot_v / (vec_length(N) * vec_length(L));
// 		//Specular light
// 		R = vec_unit(vec_sub(vec_mul(N, 2 * vec_dot(N, L)), L));
// 		dot_v = vec_dot(R, D);
// 		if (dot_v > EPSILON)
// 			intensity -= scene.light.bright * pow(dot_v / (vec_length(R) * vec_length(D)), s);
// 	}
// 	return (intensity);
// }

// double compute_lighting(t_scene scene, t_vec P, t_vec N, t_vec D)
// {
// 	t_vec		L;
// 	t_vec		R;
// 	double		intensity;
// 	double 		dot_v;
// 	double		s;

// 	s = 300;
// 	intensity = scene.ambient.ratio;
// 	L = vec_unit(vec_sub(vec(scene.light.position.x, scene.light.position.y, scene.light.position.z), P));
// 	//Diffuse light
// 	dot_v = vec_dot(N, L);
// 	if (dot_v > EPSILON)
// 		intensity += scene.light.bright * dot_v / (vec_length(N) * vec_length(L));
// 	//Specular light
// 	R = vec_unit(vec_sub(vec_mul(N, 2 * vec_dot(N, L)), L));
// 	dot_v = vec_dot(R, D);
// 	if (dot_v > EPSILON)
// 		intensity += scene.light.bright * pow(dot_v / (vec_length(R) * vec_length(D)), s);
// 	return (intensity);
// }
