/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:41:25 by adpachec          #+#    #+#             */
/*   Updated: 2023/10/17 15:52:35 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	vec_result;

	vec_result.x = v1.x + v2.x;
	vec_result.y = v1.y + v2.y;
	vec_result.z = v1.z + v2.z;
	return (vec_result);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	vec_result ;

	vec_result.x = v1.x - v2.x;
	vec_result.y = v1.y - v2.y;
	vec_result.z = v1.z - v2.z;
	return (vec_result);
}

t_vec	vec_mul(t_vec v, double t)
{
	t_vec	vec_result;

	vec_result.x = v.x * t;
	vec_result.y = v.y * t;
	vec_result.z = v.z * t;
	return (vec_result);
}

t_vec	vec(double x, double y, double z)
{
	t_vec	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}

/**
 * @brief Rotates a vector based on a given direction.
 * 
 * This function rotates the input vector `v` based on the direction vector `d`.
 * It first determines the coordinate system defined by the direction vector and
 * then applies the rotation to the input vector using this coordinate system.
 * 
 * @param v The vector to be rotated.
 * @param d The direction vector defining the rotation.
 * 
 * @return The rotated vector.
 */

t_vec	vec_rotate(t_vec v, t_vec d)
{
	t_vec	x_axis;
	t_vec	y_axis;
	t_vec	z_axis;
	t_vec	rotated;

	z_axis = vec_unit(d);
	if (d.y == 1)
		x_axis = (t_vec){-1, 0, 0};
	else if (d.y == -1)
		x_axis = (t_vec){1, 0, 0};
	else
		x_axis = vec_unit(vec_cross((t_vec){0, 1, 0}, z_axis));
	y_axis = vec_unit(vec_cross(z_axis, x_axis));
	rotated.x = v.x * x_axis.x + v.y * y_axis.x + v.z * z_axis.x;
	rotated.y = v.x * x_axis.y + v.y * y_axis.y + v.z * z_axis.y;
	rotated.z = v.x * x_axis.z + v.y * y_axis.z + v.z * z_axis.z;
	return (rotated);
}
