/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:46:53 by adpachec          #+#    #+#             */
/*   Updated: 2023/10/15 20:51:57 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

int	get_rgb(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}

int	write_color(t_point3 pixel_color)
{
	if (pixel_color.x > 255)
		pixel_color.x = 255;
	if (pixel_color.y > 255)
		pixel_color.y = 255;
	if (pixel_color.z > 255)
		pixel_color.z = 255;
	if (pixel_color.x < 0)
		pixel_color.x = 0;
	if (pixel_color.y < 0)
		pixel_color.y = 0;
	if (pixel_color.z < 0)
		pixel_color.z = 0;
	return ((int)pixel_color.x << 16
		| (int)pixel_color.y << 8 | (int)pixel_color.z);
}
