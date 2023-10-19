/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:44:31 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/19 11:38:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

/**
 * @brief Calculate the intersection point of a ray with a disk.
 * 
 * This function computes the intersection of a ray with a disk defined by its center,
 * normal, and radius. If there's no intersection, it returns INFINITY.
 * 
 * @param ray The ray to be checked for intersection.
 * @param center The center of the disk.
 * @param normal The normal vector of the disk.
 * @param radius The radius of the disk.
 * 
 * @return The intersection point's t-value, or INFINITY if no intersection.
 */

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
	if (vec_length(vec_sub(p, center)) - radius > EPSILON)
		return (INFINITY);
	return (t);
}

/**
 * @brief Calculate the minimum t-value for a ray-cone intersection.
 * 
 * This function determines the closest intersection point of a ray with a cone.
 * It checks if the intersection is within the bounds of the cone's height.
 * 
 * @param t1 The first potential intersection point's t-value.
 * @param t2 The second potential intersection point's t-value.
 * @param co Pointer to the cone structure.
 * @param ray The intersecting ray.
 * 
 * @return The minimum t-value if the intersection is valid, otherwise INFINITY.
 */

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

/**
 * @brief Solve the quadratic equation for ray-cone intersection.
 * 
 * This function computes the solutions to the quadratic equation that arises
 * from the intersection of a ray with a cone. It then determines the closest
 * valid intersection point.
 * 
 * @param co Pointer to the cone structure.
 * @param r Direction vector of the ray.
 * @param v Vector from the ray's origin to the cone's vertex.
 * @param ray The intersecting ray.
 * 
 * @return The closest intersection point's t-value, or INFINITY if no intersection.
 */

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

/**
 * @brief Determine the intersection of a ray with a cone.
 * 
 * This function calculates the intersection point of a ray with a cone. It considers
 * both the conical surface and the base of the cone. If there's no intersection,
 * it sets the t-value to INFINITY.
 * 
 * @param ray The ray to be checked for intersection.
 * @param co Pointer to the cone structure.
 * @param t Pointer to store the intersection point's t-value.
 */

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
