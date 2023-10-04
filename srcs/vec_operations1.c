/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:41:25 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/27 23:13:40 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vec	 vec_add (t_vec v1 , t_vec v2) 
{ 
	t_vec	vec_result;

	vec_result.x = v1.x + v2.x;
	vec_result.y = v1.y + v2.y;
	vec_result.z = v1.z + v2.z;
	return (vec_result);
}

t_vec	 vec_sub (t_vec v1 , t_vec v2) 
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

	vec_result . x = v.x * t ; 
	vec_result . y = v.y * t ; 
	vec_result . z = v.z * t ; 
	return (vec_result) ; 
}

t_vec	vec(double x, double y, double z)
{
	t_vec	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}

t_vec vec_rotate(t_vec v, t_vec d)
{
	t_vec	a;
	t_vec	b;
	t_vec   v_rotated;

	d = vec_unit(d);
	if (d.x != 0 || d.y != 0)
		a = vec_unit(vec_cross((t_vec){0, 0, 1}, d));
    else
 		a = vec_unit(vec_cross((t_vec){0, 1, 0}, d));
	b = vec_unit(vec_cross(a, d));
	v_rotated.x = -a.x * v.x - b.x * v.y + d.x * v.z;
	v_rotated.y = a.y * v.x - b.y * v.y + d.y * v.z;
	v_rotated.z = a.z * v.x + b.z * v.y + d.z * v.z;
	return (v_rotated);
}
