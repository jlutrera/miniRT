/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:44:31 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/15 16:32:10 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static double	intersect_disk(t_ray ray, t_vec center,
		t_vec normal, double radius)
{
	double	denom;
	double	t;
	t_vec	p;

	denom = vec_dot(normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return (INFINITY);
	t = vec_dot(vec_sub(center, point_to_vec(ray.origin)), normal) / denom;
	if (t < EPSILON)
		return (INFINITY);
	p = vec_add(point_to_vec(ray.origin), vec_mul(ray.dir, t));
	if (vec_length(vec_sub(p, center)) > radius)
		return (INFINITY);
	return (t);
}

static double	calc_tmin(double t1, double t2, t_cone *co, t_ray ray)
{
	double	t_min;
	t_vec	p;
	double	h;

	if (t1 < 0)
		t1 = INFINITY;
	if (t2 < 0)
		t2 = INFINITY;
	if (t1 < t2)
		t_min = t1;
	else
		t_min = t2;
	if (t_min != INFINITY)
	{
		p = vec_add(point_to_vec(ray.origin),
				vec_mul(vec_unit(ray.dir), t_min));
		h = vec_dot(vec_sub(p, point_to_vec(co->coordinate)),
				vec_unit(co->direction));
		if (h < EPSILON || h - co->height > EPSILON)
			t_min = INFINITY;
	}
	return (t_min);
}

static double	solve_equation(t_cone *co, t_vec r, t_vec vo, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	x;
	t_vec	d;

	d = vec_unit(co->direction);
	x = atan2(co->radius, co->height);
	a = vec_dot(r, d) * vec_dot(r, d) - cos(x) * cos(x);
	b = -2 * vec_dot(vo, d) * vec_dot(d, r) + 2 * vec_dot(vo, r)
		* cos(x) * cos(x);
	c = vec_dot(vo, d) * vec_dot(vo, d) - vec_dot(vo, vo)
		* cos(x) * cos(x);
	x = b * b - 4 * a * c;
	if (x < EPSILON)
		return (INFINITY);
	x = sqrt(x);
	return (calc_tmin((-b + x) / (2 * a), (-b - x) / (2 * a), co, ray));
}

void	intersect_co(t_ray ray, t_cone *co, t_point *t)
{
	double	t_base;
	double	t_min;
	t_vec	vertex;
	t_vec	vo;

	vertex = vec_add(point_to_vec(co->coordinate),
			vec_mul(vec_unit(co->direction), co->height));
	vo = vec_sub(vertex, point_to_vec(ray.origin));
	t_min = solve_equation(co, vec_unit(ray.dir), vo, ray);
	t_base = intersect_disk(ray, point_to_vec(co->coordinate),
			vec_unit(co->direction), co->radius);
	if (t_base < t_min)
		t_min = t_base;
	*t = (t_point){t_min, t_min};
}
