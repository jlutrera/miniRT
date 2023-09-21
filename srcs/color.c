/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:46:53 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/18 13:51:12 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	get_rgb(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}

int write_color(t_point3 pixel_color)
{
	return ((int)(255.999 * pixel_color.x) << 16 |
		(int)(255.999 * pixel_color.y) << 8 | (int)(255.999 * pixel_color.z));
}
