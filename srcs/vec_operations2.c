/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:26:08 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/18 13:41:59 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	v_module(t_vec vec)
{
	return (sqrt(pow(vec.x, 2.0) + pow(vec.y, 2.0) + pow(vec.z, 2.0)));
}

double vec_dot(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec vec_cross(t_vec *v1,t_vec * v2 ) 
{ 
	t_vec	vec_result ;

	vec_result.x = v1->y * v2->z + v1->z * v2->y;
	vec_result.y = v1->z * v2->x + v1->x * v2->z;
	vec_result.z = v1->x * v2->y + v1->y * v2->x;
	return (vec_result);
}

double vec_length(t_vec v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec vec_unit(t_vec v)
{
	double	len;
	t_vec	unit_vec;

	len =  vec_length(v);
	unit_vec = vec(v.x / len, v.y / len, v.z / len);
	return (unit_vec);
}

