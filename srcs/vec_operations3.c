/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:33:31 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 19:48:25 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

t_vec	point_to_vec(t_point3 p)
{
	t_vec	new_vec;

	new_vec.x = p.x;
	new_vec.y = p.y;
	new_vec.z = p.z;
	return (new_vec);
}

t_point3	vec_to_point(t_vec v)
{
	t_point3	p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	return (p);
}
