/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:01:36 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 20:20:16 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	intersect_disk(t_ray ray, t_vec center, t_vec normal, double radius)
{
	double	denom;
	double	t;
	t_vec	p;

	denom = vec_dot(normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return (INFINITY);
	t = vec_dot(vec_sub(center, point_to_vec(ray.origin)), normal) / denom;
	if (t < EPSILON)
		return (INFINITY);
	p = vec_add(point_to_vec(ray.origin), vec_mul(ray.dir, t));
	if (vec_length(vec_sub(p, center)) > radius)
		return (INFINITY);
	return (t);
}

void	intersect_cylinder(t_ray ray, t_cylinder *cy, t_point *t)
{
	t_vec cd = vec_unit(cy->direction);
	
	t_vec OC = vec_sub(point_to_vec(ray.origin), point_to_vec(cy->coordinate));
	t_vec OC_perp = vec_sub(OC, vec_mul(cd, vec_dot(OC, cd)));
	t_vec OD_perp = vec_sub(ray.dir, vec_mul(cd, vec_dot(ray.dir, cd)));

	if (vec_length(OD_perp) < EPSILON) 
		OD_perp = vec(ray.dir.y,-ray.dir.x,ray.dir.z);
	
	double a = vec_dot(OD_perp, OD_perp);
	double b = 2 * vec_dot(OC_perp, OD_perp);
	double c = vec_dot(OC_perp, OC_perp) - cy->radius * cy->radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant < EPSILON)
	{
		*t = (t_point){INFINITY, INFINITY};
		return ;
	}
	double sqrt_discriminant = sqrt(discriminant);
	double t1 = (-b + sqrt_discriminant) / (2 * a);
	double t2 = (-b - sqrt_discriminant) / (2 * a);

	t_vec P1 = vec_add(point_to_vec(ray.origin), vec_mul(ray.dir, t1));
	t_vec P2 = vec_add(point_to_vec(ray.origin), vec_mul(ray.dir, t2));

	double h1 = vec_dot(vec_sub(P1, point_to_vec(cy->coordinate)), cd);
	double h2 = vec_dot(vec_sub(P2, point_to_vec(cy->coordinate)), cd);

	if (h1 < EPSILON || h1 > cy->height)
		t1 = INFINITY;
	if (h2 < EPSILON || h2 > cy->height)
		t2 = INFINITY;
	
	double t_base1 = intersect_disk(ray, point_to_vec(cy->coordinate), cd, cy->radius);
	double t_base2 = intersect_disk(ray, vec_add(point_to_vec(cy->coordinate), vec_mul(cd, cy->height)), cd, cy->radius);
	
	double t_values[4] = {t1, t2, t_base1, t_base2};
	double t_min = INFINITY;
	for(int i = 0; i < 4; i++)
	{
		if (t_values[i] > EPSILON && t_values[i] < t_min)
			t_min = t_values[i];
	}
	*t = (t_point){t_min, INFINITY};
}

t_point3	compute_cylinder_light(t_cylinder *cy, t_scene scene,
		t_vec p, t_ray ray)
{
	t_vec	n;
	double	i;
	double	h;
	t_vec	op;
	t_vec	proj;

	h = vec_dot(vec_sub(p, point_to_vec(cy->coordinate)), cy->direction);
	if (fabs(h - cy->height) < EPSILON || fabs(h) < EPSILON)
		n = vec_unit(cy->direction);
	else
	{
		op = vec_unit(vec_sub(p, point_to_vec(cy->coordinate)));
		proj = vec_mul(cy->direction, vec_dot(op, cy->direction));
		n = vec_unit(vec_sub(op, proj));
	}
	i = compute_lighting(scene, p, n, vec_unit(vec_mul(ray.dir, -1)));
	i += compute_shadows(scene, p, n, vec_unit(vec_mul(ray.dir, 1)));
	return ((t_point3){cy->color.r * i, cy->color.g * i, cy->color.b * i});
}

int	ft_load_cylinders(t_lst_obj **obj, char **s)
{
	int			e;
	t_cylinder	*new_cy;

	if (check_comps(s, 6))
		return (NUM_COMPONENTS_E);
	new_cy = new_cylinder(s, &e);
	if (!new_cy)
		return (e);
	ft_add_back_obj(obj, (void **)&new_cy, CYLINDER, ft_get_dist());
	return (SUCCESS);
}

t_cylinder	*new_cylinder(char **s, int *e)
{
	t_cylinder	*new_cy;

	new_cy = ft_calloc(sizeof(t_cylinder *), 1);
	if (!new_cy)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	new_cy->radius = ft_atod(s[3]) / 2;
	new_cy->height = ft_atod(s[4]);
	if (ft_get_point(s[1], &new_cy->coordinate) == -1
		|| ft_get_vector(s[2], &new_cy->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_cy->direction))
		*e = NORM_VECTOR_E;
	else if (new_cy->radius <= 0 || new_cy->height <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[5], &new_cy->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_cy);
	return (free(new_cy), NULL);
}
