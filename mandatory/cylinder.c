/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:38:14 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/19 08:54:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

/**
 * @brief Computes the lighting and shadow effects on a cylinder at a given point.
 * 
 * This function calculates the lighting and shadow effects on a cylinder at a specific point.
 * It determines the normal at the point, computes the lighting intensity, and adjusts for shadows.
 * 
 * @param cy The cylinder object.
 * @param scene The scene containing objects, lights, etc.
 * @param p The point on the cylinder.
 * 
 * @return The color of the cylinder at the point after considering lighting and shadows.
 */

t_point3	compute_cy_light(t_cylinder *cy, t_scene scene, t_vec p)
{
	t_vec		n;
	t_point3	i;
	t_vec		op;
	t_point3	intensity;
	double		shadow;

	op = vec_sub(p, point_to_vec(cy->coordinate));
	i.x = vec_dot(op, vec_unit(cy->direction));
	if (fabs(i.x - cy->height) <= EPSILON)
		n = vec_unit(cy->direction);
	else if (fabs(i.x) <= EPSILON)
		n = vec_unit(vec_mul(cy->direction, -1));
	else
		n = vec_unit(vec_sub(op, vec_mul(vec_unit(cy->direction), i.x)));
	i = compute_lighting(scene, p, n);
	shadow = compute_shadows(scene, p, n);
	intensity.x = i.x - shadow + scene.ambient.ratio
		* scene.ambient.color.r / 255 ;
	intensity.y = i.y - shadow + scene.ambient.ratio
		* scene.ambient.color.g / 255 ;
	intensity.z = i.z - shadow + scene.ambient.ratio
		* scene.ambient.color.b / 255;
	return ((t_point3){fmax(10, intensity.x * cy->color.r), fmax(10,
			intensity.y * cy->color.g), fmax(10, intensity.z * cy->color.b)});
}

int	ft_load_cy(t_lst_obj **obj, char **s)
{
	int			e;
	t_cylinder	*new_cylinder;

	if (check_comps(s, 6))
		return (NUM_COMPONENTS_E);
	new_cylinder = new_cy(s, &e);
	if (!new_cylinder)
		return (e);
	ft_add_back_obj(obj, (void **)&new_cylinder, CYLINDER, ft_get_dist());
	return (SUCCESS);
}

/**
 * @brief Creates a new cylinder object from parsed data.
 * 
 * This function allocates memory for a new cylinder object and initializes it using
 * the parsed data. It checks for errors in the data and returns the cylinder if successful.
 * 
 * @param s The parsed data for the cylinder.
 * @param e Pointer to an error code variable.
 * 
 * @return A pointer to the new cylinder object if successful, NULL otherwise.
 */

t_cylinder	*new_cy(char **s, int *e)
{
	t_cylinder	*new_cylinder;

	new_cylinder = ft_calloc(sizeof(t_cylinder), 1);
	if (!new_cylinder)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	new_cylinder->radius = ft_atod(s[3]) / 2;
	new_cylinder->height = ft_atod(s[4]);
	if (ft_get_point(s[1], &new_cylinder->coordinate) == -1
		|| ft_get_vector(s[2], &new_cylinder->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_cylinder->direction))
		*e = NORM_VECTOR_E;
	else if (new_cylinder->radius <= 0 || new_cylinder->height <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[5], &new_cylinder->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_cylinder);
	return (free(new_cylinder), NULL);
}
