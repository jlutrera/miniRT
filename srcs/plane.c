#include "../include/miniRT.h"

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

t_point3	compute_plane_light(t_plane *pl, t_scene scene, t_vec P, t_ray ray)
{
	t_vec 		N;
	double 		i;

	N = vec_unit(pl->direction);
	i = compute_lighting(scene, P, N, vec_mul(ray.dir, -1));
	i += compute_shadows(scene, P, N, vec_mul(ray.dir, -1));
	return (t_point3){pl->color.r * i, pl->color.g * i, pl->color.b * i};
}

t_plane	*new_plane(char **s, int *e)
{
	t_plane	*new_pl;

	new_pl = ft_calloc(sizeof(t_plane *), 1);
	if (!new_pl)
	{
		*e = MEMORY_E;		
		return NULL;
	}
	*e = SUCCESS;
	if (ft_get_point(s[1], &new_pl->coordinate) == -1 ||
		ft_get_vector(s[2], &new_pl->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_pl->direction))
		*e = NORM_VECTOR_E;
	else if (ft_get_color(s[3], &new_pl->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_pl);
	return free(new_pl), NULL;
}

int	ft_load_planes(t_lst_obj **obj, char **s)
{
	int			e;
	t_plane		*new_pl;

	if (check_comps(s, 4))
		return NUM_COMPONENTS_E;
	new_pl = new_plane(s, &e);
	if (!new_pl)
		return e;
	ft_add_back_obj(obj, (void**) &new_pl, PLANE, ft_get_dist());
	return SUCCESS;
}