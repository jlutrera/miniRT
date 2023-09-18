/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:41:25 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/18 13:42:05 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vec	 vec_add (t_vec *v1 , t_vec *v2) 
{ 
	t_vec	vec_result;

	vec_result.x = v1->x + v2->x;
	vec_result.y = v1->y + v2->y;
	vec_result.z = v1->z + v2->z;
	return (vec_result);
}

t_vec	 vec_sub (t_vec *v1 , t_vec *v2) 
{ 
	t_vec	vec_result ;

	vec_result.x = v1->x - v2->x;
	vec_result.y = v1->y - v2->y;
	vec_result.z = v1->z - v2->z;
	return (vec_result);
}

t_vec	vec_mul(t_vec *v1, double t)
{
	t_vec	vec_result;

	vec_result . x = v1 -> x * t ; 
	vec_result . y = v1 -> y * t ; 
	vec_result . z = v1 -> z * t ; 
	return (vec_result) ; 
}

t_vec	vec_cal(t_vec *v, double *a, int n)
{
	t_vec	vec_result;

	vec_result = vec(0, 0, 0);
	while (n--)
	{
		vec_result.x += v[n].x * a[n];
		vec_result.y += v[n].y * a[n];
		vec_result.z += v[n].z * a[n];
	}
	return (vec_result);
}

t_vec vec(double x, double y, double z)
{
	t_vec	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}

