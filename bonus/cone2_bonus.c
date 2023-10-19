/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:44:31 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/19 18:57:21 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static double	intersect_disk(t_ray ray, t_vec center,
		t_vec normal, double radius)
{
	double	denom;
	double	num;
	double	t;
	t_vec	p;

	denom = vec_dot(normal, ray.dir);
	if (fabs(denom) <= EPSILON)
		return (INFINITY);
	num = vec_dot(normal, vec_sub(center, point_to_vec(ray.origin)));
	t = num / denom;
	if (t < EPSILON)
		return (INFINITY);
	p = vec_add(point_to_vec(ray.origin), vec_mul(ray.dir, t));
	if (vec_length(vec_sub(p, center)) - radius >= EPSILON)
		return (INFINITY);
	return (t);
}

static double	calc_tmin(double t1, double t2, t_cone *co, t_ray ray)
{
	t_vec	p;
	double	h;
	double	t_min;

	if (t1 <= EPSILON)
		t1 = INFINITY;
	if (t2 <= EPSILON)
		t2 = INFINITY;
	if (t1 < t2)
		t_min = t1;
	else
		t_min = t2;
	if (t_min == INFINITY)
		return (INFINITY);
	p = vec_add(point_to_vec(ray.origin),
			vec_mul(vec_unit(ray.dir), t_min));
	h = vec_dot(vec_sub(p, point_to_vec(co->coordinate)),
			vec_unit(co->direction));
	if (h < EPSILON || h - co->height > EPSILON)
		return (INFINITY);
	return (t_min);
}

static double	solve_equation(t_cone *co, t_vec d, t_vec v, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	x;
	t_vec	oc;

	oc = vec_add(point_to_vec(co->coordinate),
			vec_mul(vec_unit(co->direction), co->height));
	oc = vec_sub(point_to_vec(ray.origin), oc);
	x = 1 + pow(co->radius / co->height, 2);
	a = vec_dot(d, d) - x * pow(vec_dot(d, v), 2);
	b = 2 * (vec_dot(d, oc) - x * vec_dot(d, v) * vec_dot(oc, v));
	c = vec_dot(oc, oc) - x * pow(vec_dot(oc, v), 2);
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
	t_vec	v;

	v = vec_unit(vec_mul(co->direction, -1));
	t_min = solve_equation(co, vec_unit(ray.dir), v, ray);
	t_base = intersect_disk(ray, point_to_vec(co->coordinate),
			vec_unit(co->direction), co->radius);
	if (t_base < t_min)
		t_min = t_base;
	*t = (t_point){t_min, INFINITY};
}
