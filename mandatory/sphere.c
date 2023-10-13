/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:49:01 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/09 11:28:55 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_load_sp(t_lst_obj **obj, char **s)
{
	int			e;
	t_sphere	*new_sphere;

	if (check_comps(s, 4))
		return (NUM_COMPONENTS_E);
	new_sphere = new_sp(s, &e);
	if (!new_sphere)
		return (e);
	ft_add_back_obj(obj, (void **)&new_sphere, SPHERE, ft_get_dist());
	return (SUCCESS);
}

t_sphere	*new_sp(char **s, int *e)
{
	t_sphere	*new_sphere;

	new_sphere = ft_calloc(sizeof(t_sphere), 1);
	if (!new_sphere)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	new_sphere->radius = ft_atod(s[2]) / 2;
	*e = SUCCESS;
	if (ft_get_point(s[1], &new_sphere->center) == -1)
		*e = BAD_COORDINATES_E;
	else if (new_sphere->radius <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[3], &new_sphere->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_sphere);
	return (free(new_sphere), NULL);
}

void	intersect_sp(t_ray ray, t_sphere *sp, t_point *t)
{
	t_vec	co;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	co = vec_sub(point_to_vec(ray.origin), point_to_vec(sp->center));
	a = vec_dot(ray.dir, ray.dir);
	b = 2 * vec_dot(co, ray.dir);
	c = vec_dot(co, co) - sp->radius * sp->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < EPSILON)
		*t = (t_point){INFINITY, INFINITY};
	else
		*t = (t_point){(-b + sqrt(discriminant))
			/ (2 * a), (-b - sqrt(discriminant)) / (2 * a)};
}

t_point3	compute_sp_light(t_sphere *sp, t_scene scene, t_vec p)
{
	t_vec		n;
	t_point3	i;
	double		shadow;
	t_point3	intensity;

	n = vec_unit(vec_sub(p, point_to_vec(sp->center)));
	i = compute_lighting(scene, p, n);
	shadow = compute_shadows(scene, p, n);
	intensity.x = i.x - shadow + scene.ambient.ratio
		* scene.ambient.color.r / 255;
	intensity.y = i.y - shadow + scene.ambient.ratio
		* scene.ambient.color.g / 255;
	intensity.z = i.z - shadow + scene.ambient.ratio
		* scene.ambient.color.b / 255;
	return ((t_point3){fmax(10, intensity.x * sp->color.r), fmax(10,
			intensity.y * sp->color.g), fmax(10, intensity.z * sp->color.b)});
}
