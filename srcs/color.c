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

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int write_color(int t, t_color *pixel_color)
{
	return (t << 24 | (255 * pixel_color->r) << 16 |
		(255 * pixel_color->g) << 8 | (255 * pixel_color->b));
}
