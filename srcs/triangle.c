#include "../include/miniRT.h"

static bool point_is_inside_triangle(t_triangle *tr, t_vec p, t_vec n)
{
	t_vec	edge;
	t_vec	c;

	edge = (t_vec){tr->p2.x - tr->p1.x, tr->p2.y - tr->p1.y, tr->p2.z - tr->p1.z};
	c = vec_cross(edge, (t_vec){p.x - tr->p1.x, p.y - tr->p1.y, p.z - tr->p1.z});
	if (vec_dot(n, c) < EPSILON)
		return (false);
	edge = (t_vec){tr->p3.x - tr->p2.x, tr->p3.y - tr->p2.y, tr->p3.z - tr->p2.z};
	c = vec_cross(edge, (t_vec){p.x - tr->p2.x, p.y - tr->p2.y, p.z - tr->p2.z});
	if (vec_dot(n, c) < EPSILON)
		return (false);
	edge = (t_vec){tr->p1.x - tr->p3.x, tr->p1.y - tr->p3.y, tr->p1.z - tr->p3.z};
	c = vec_cross(edge, (t_vec){p.x - tr->p3.x, p.y - tr->p3.y, p.z - tr->p3.z});
	if (vec_dot(n, c) < EPSILON)
		return (false);
	return (true);
}

void	intersect_triangle(t_ray ray, t_triangle *tr, t_point *t)
{
	t_vec	edge1;
	t_vec	edge2;
	t_vec	n;
	t_point v;
	t_vec	p;

	edge1 = (t_vec){tr->p2.x - tr->p1.x, tr->p2.y - tr->p1.y, tr->p2.z - tr->p1.z};
	edge2 = (t_vec){tr->p3.x - tr->p1.x, tr->p3.y - tr->p1.y, tr->p3.z - tr->p1.z};
	n = vec_cross(edge1, edge2);
	v.x = vec_dot(ray.dir, n);
	if (fabs(v.x) < EPSILON) //rayo paralelo al plano, es decir: n y ray.dir son perpendiculares
		return ;
	v.y = vec_dot(point_to_vec(tr->p1), n);
	t->x = (v.y - vec_dot(point_to_vec(ray.origin), n)) / v.x;
	if (t->x < 0)
	{
		*t = (t_point){INFINITY, INFINITY};
		return ;
	}
	p = vec_add(point_to_vec(ray.origin), vec_mul(ray.dir, t->x));
	if (point_is_inside_triangle(tr, p, n))
		*t = (t_point){t->x, INFINITY};
	else
		*t = (t_point){INFINITY, INFINITY};
}

t_point3	compute_triangle_colour_light(t_triangle *tr, t_scene scene,
		t_vec p)
{
	t_vec		n;
	t_point3	i;
	double		shadow;
	t_point3	intensity;

	i = compute_colour_lighting(scene, p, n);
	shadow = compute_shadows(scene, p, n);
	intensity.x = i.x - shadow + scene.ambient.ratio
		* scene.ambient.color.r / 255;
	intensity.y = i.y - shadow + scene.ambient.ratio
		* scene.ambient.color.g / 255;
	intensity.z = i.z - shadow + scene.ambient.ratio
		* scene.ambient.color.b / 255;
	return ((t_point3){fmax(10, intensity.x * tr->color.r), fmax(10,
			intensity.y * tr->color.g), fmax(10, intensity.z * tr->color.b)});
}

t_triangle	*new_triangle(char **s, int *e)
{
	t_triangle	*new_tr;

	new_tr = ft_calloc(sizeof(t_triangle), 1);
	if (!new_tr)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	if (ft_get_point(s[1], &new_tr->p1) == -1)
		*e = BAD_COORDINATES_E;
	else if (ft_get_point(s[2], &new_tr->p2) == -1)
		*e = BAD_COORDINATES_E;
	else if (ft_get_point(s[3], &new_tr->p3) == -1)
		*e = BAD_COORDINATES_E;
	else if (ft_get_color(s[4], &new_tr->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_tr);
	return (free(new_tr), NULL);
}

int	ft_load_triangles(t_lst_obj **obj, char **s)
{
	int			e;
	t_triangle	*new_tr;

	if (check_comps(s, 5))
		return (NUM_COMPONENTS_E);
	new_tr = new_triangle(s, &e);
	if (!new_tr)
		return (e);
	ft_add_back_obj(obj, (void **)&new_tr, TRIANGLE, ft_get_dist());
	return (SUCCESS);
}
