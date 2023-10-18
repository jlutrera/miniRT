/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:55:04 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/18 12:40:30 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/**
 * @brief Determines the intersection point between a ray and a plane.
 * 
 * This function calculates the intersection point of a ray with a plane.
 * The plane is defined by its coordinate and direction.
 * 
 * @param ray The ray to check for intersection.
 * @param plane The plane object.
 * @param t Pointer to a structure that will store the intersection distance.
 */

void	intersect_pl(t_ray ray, t_plane *plane, t_point *t)
{
	t_vec	op;
	double	denom;
	double	num;

	denom = vec_dot(plane->direction, ray.dir);
	op = vec_sub(point_to_vec(plane->coordinate), point_to_vec(ray.origin));
	num = vec_dot(plane->direction, op);
	if (fabs(denom) < EPSILON)
		*t = (t_point){INFINITY, INFINITY};
	else
		*t = (t_point){num / denom, num / denom};
}

/**
 * @brief Computes the lighting effect on a plane at a given point.
 * 
 * This function calculates the lighting effect on a plane at a specific
 * point.
 * It takes into account the ambient, diffuse, and specular components of the
 * light.
 * 
 * @param pl The plane object.
 * @param scene The scene containing all the objects and lights.
 * @param p The point on the plane where the lighting effect is to be computed.
 * 
 * @return The color of the plane at the given point after applying the lighting
 * effect.
 */

t_point3	compute_pl_light(t_plane *pl, t_scene scene, t_vec p)
{
	t_vec		n;
	t_point3	i;
	t_point3	intensity;
	double		shadow;

	n = vec_unit(pl->direction);
	i = compute_lighting(scene, p, n);
	shadow = compute_shadows(scene, p, n);
	intensity.x = i.x - shadow + scene.ambient.ratio
		* scene.ambient.color.r / 255 ;
	intensity.y = i.y - shadow + scene.ambient.ratio
		* scene.ambient.color.g / 255 ;
	intensity.z = i.z - shadow + scene.ambient.ratio
		* scene.ambient.color.b / 255;
	return ((t_point3){fmax(10, intensity.x * pl->color.r), fmax(10,
			intensity.y * pl->color.g), fmax(10, intensity.z * pl->color.b)});
}

/**
 * @brief Creates a new plane object from the given input string.
 * 
 * This function parses the input string to extract the properties of the
 * plane
 * such as its coordinate, direction, and color. It then creates a new plane
 * object with these properties.
 * 
 * @param s The input string containing the plane's properties.
 * @param e Pointer to an integer that will store any error code.
 * 
 * @return A pointer to the newly created plane object or NULL if there's an
 * error.
 */

t_plane	*new_pl(char **s, int *e)
{
	t_plane	*new_plane;

	new_plane = ft_calloc(sizeof(t_plane), 1);
	if (!new_plane)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	if (ft_get_point(s[1], &new_plane->coordinate) == -1
		|| ft_get_vector(s[2], &new_plane->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_plane->direction))
		*e = NORM_VECTOR_E;
	else if (ft_get_color(s[3], &new_plane->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_plane);
	return (free(new_plane), NULL);
}

int	ft_load_pl(t_lst_obj **obj, char **s)
{
	int			e;
	t_plane		*new_plane;

	if (check_comps(s, 4))
		return (NUM_COMPONENTS_E);
	new_plane = new_pl(s, &e);
	if (!new_plane)
		return (e);
	ft_add_back_obj(obj, (void **)&new_plane, PLANE, ft_get_dist());
	return (SUCCESS);
}
