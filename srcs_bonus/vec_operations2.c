/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:26:08 by adpachec          #+#    #+#             */
/*   Updated: 2023/10/06 19:47:06 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	vec_result ;

	vec_result.x = v1.y * v2.z - v1.z * v2.y;
	vec_result.y = v1.z * v2.x - v1.x * v2.z;
	vec_result.z = v1.x * v2.y - v1.y * v2.x;
	return (vec_result);
}

double	vec_length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	vec_unit(t_vec v)
{
	double	len;
	t_vec	unit_vec;

	len = vec_length(v);
	if (len == 1 || len == 0)
		return (v);
	unit_vec = vec(v.x / len, v.y / len, v.z / len);
	return (unit_vec);
}

t_vec	vec_divition(t_vec v1, double t)
{
	t_vec	vec_result;

	if (t == 0)
		return (v1);
	vec_result.x = v1.x / t;
	vec_result.y = v1.y / t;
	vec_result.z = v1.z / t;
	return (vec_result);
}
