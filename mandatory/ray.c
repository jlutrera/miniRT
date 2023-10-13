/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:55:16 by adpachec          #+#    #+#             */
/*   Updated: 2023/10/06 19:43:11 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_ray	ray(t_point3 origin, t_vec dir)
{
	t_ray	new_ray;

	new_ray.origin.x = origin.x;
	new_ray.origin.y = origin.y;
	new_ray.origin.z = origin.z;
	new_ray.dir.x = dir.x;
	new_ray.dir.y = dir.y;
	new_ray.dir.z = dir.z;
	return (new_ray);
}

t_vec	ray_ex(t_ray *ray, double t)
{
	t_vec	ray_expression;

	ray_expression.x = ray -> origin.x + ray -> dir.x * t ;
	ray_expression.y = ray -> origin.y + ray -> dir.y * t ;
	ray_expression.z = ray -> origin.z + ray -> dir.z * t ;
	return (ray_expression);
}
