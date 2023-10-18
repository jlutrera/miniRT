/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:38:21 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/17 15:53:36 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

/**
 * @brief Calculate the normal vector of a cone at a given point.
 * 
 * This function computes the normal vector of a cone at a point `cp` on its surface.
 * The normal is determined based on the cone's direction and its geometric properties.
 * 
 * @param co Pointer to the cone structure.
 * @param cp Point on the cone's surface.
 * 
 * @return The normal vector at point `cp` on the cone.
 */

t_vec	calc_normal(t_cone *co, t_vec cp)
{
	t_vec	d;
	double	alfa;
	t_vec	ca;
	t_vec	ap;
	t_vec	v;

	d = vec_unit(co->direction);
	alfa = atan2(co->radius, co->height);
	ca = vec_mul(d, vec_dot(cp, d));
	ap = vec_sub(cp, ca);
	v = vec_cross(d, ap);
	return (vec_unit(vec_sub(vec_mul(ap, cos(alfa)), vec_mul(v, sin(alfa)))));
}

/**
 * @brief Compute the color of a cone under lighting conditions.
 * 
 * This function calculates the color of a cone at a point `p` considering the scene's
 * lighting conditions. It takes into account ambient, diffuse, and shadow effects.
 * 
 * @param co Pointer to the cone structure.
 * @param scene The scene containing lighting and other objects.
 * @param p Point on the cone's surface.
 * 
 * @return The computed color at point `p` on the cone.
 */

t_point3	compute_co_colour_light(t_cone *co, t_scene scene, t_vec p)
{
	t_vec		n;
	t_point3	i;
	t_point3	intensity;
	t_point3	shadow;
	t_vec		cp;

	cp = vec_sub(p, point_to_vec(co->coordinate));
	if (fabs(vec_length(cp) - co->radius) < EPSILON)
		n = vec_mul(vec_unit(co->direction), -1);
	else
		n = calc_normal(co, cp);
	i = compute_colour_lighting(scene, p, n);
	shadow = compute_shadows(scene, p, n);
	intensity.x = i.x - shadow.x + scene.ambient.ratio
		* scene.ambient.color.r / 255 ;
	intensity.y = i.y - shadow.y + scene.ambient.ratio
		* scene.ambient.color.g / 255 ;
	intensity.z = i.z - shadow.z + scene.ambient.ratio
		* scene.ambient.color.b / 255;
	return ((t_point3){fmax(10, intensity.x * co->color.r), fmax(10,
			intensity.y * co->color.g), fmax(10, intensity.z * co->color.b)});
}

/**
 * @brief Load a cone object from a string array and add it to the objects list.
 * 
 * This function parses the string array `s` to extract cone properties and then
 * adds the cone to the list of objects in the scene.
 * 
 * @param obj Pointer to the list of objects in the scene.
 * @param s String array containing cone properties.
 * 
 * @return SUCCESS if the cone is loaded successfully, otherwise an error code.
 */

int	ft_load_co(t_lst_obj **obj, char **s)
{
	int		e;
	t_cone	*new_cone;

	if (check_comps(s, 6))
		return (NUM_COMPONENTS_E);
	new_cone = new_co(s, &e);
	if (!new_cone)
		return (e);
	ft_add_back_obj(obj, (void **)&new_cone, CONE, ft_get_dist());
	return (SUCCESS);
}

/**
 * @brief Create a new cone object from a string array.
 * 
 * This function parses the string array `s` to extract cone properties and then
 * creates a new cone object. It performs various checks to ensure the validity
 * of the provided data.
 * 
 * @param s String array containing cone properties.
 * @param e Pointer to an integer to store error codes.
 * 
 * @return Pointer to the newly created cone if successful, otherwise NULL.
 */

t_cone	*new_co(char **s, int *e)
{
	t_cone	*new_cone;

	new_cone = ft_calloc(sizeof(t_cone), 1);
	if (!new_cone)
	{
		*e = MEMORY_E;
		return (NULL);
	}
	*e = SUCCESS;
	new_cone->radius = ft_atod(s[3]) / 2;
	new_cone->height = ft_atod(s[4]);
	if (ft_get_point(s[1], &new_cone->coordinate) == -1
		|| ft_get_vector(s[2], &new_cone->direction) == -1)
		*e = BAD_COORDINATES_E;
	else if (!is_normalized(new_cone->direction))
		*e = NORM_VECTOR_E;
	else if (new_cone->radius <= 0 || new_cone->height <= 0)
		*e = NEGATIVE_E;
	else if (ft_get_color(s[5], &new_cone->color) == -1)
		*e = COLOUR_E;
	if (*e == SUCCESS)
		return (new_cone);
	return (free(new_cone), NULL);
}
