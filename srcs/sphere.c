#include "../include/miniRT.h"

int ft_load_spheres(t_lst_obj **obj, char **s)
{
	int			e;
	t_sphere	*new_sp;

	if (check_comps(s, 4))
		return NUM_COMPONENTS_E;
	new_sp = new_sphere(s, &e);
	if (!new_sp)
		return e;
	ft_add_back_obj(obj, (void**) &new_sp, SPHERE, ft_get_dist());
	return (SUCCESS);
}

t_sphere	*new_sphere(char **s, int *e)
{
	t_sphere	*new_sp;

	new_sp = ft_calloc(sizeof(t_sphere *), 1);
	if (!new_sp)
	{
		*e = MEMORY_E;
		return NULL;
	}
	new_sp->radius = ft_atod(s[2]) / 2;
	*e = SUCCESS;
	if (ft_get_point(s[1], &new_sp->center) == -1)
		*e = BAD_COORDINATES_E;
	else if (new_sp->radius <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[3], &new_sp->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_sp);
	return free(new_sp), NULL;
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

t_point3	compute_sphere_light(t_sphere *sp, t_scene scene, t_vec P, t_ray ray)
{
	t_vec 		N;
	double 		i;

	N = vec_unit(vec_sub(P, vec(sp->center.x, sp->center.y, sp->center.z)));
	i = compute_lighting(scene, P, N, vec_mul(ray.dir, -1));
	i += compute_shadows(scene, P, N, vec_mul(ray.dir, -1));
	return (t_point3){sp->color.r * i, sp->color.g * i, sp->color.b * i};
}