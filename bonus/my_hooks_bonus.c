/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:52:42 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/15 20:53:00 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static int	ft_close(t_data *vars)
{
	mlx_destroy_image(vars->vars.mlx, vars->image.img);
	mlx_destroy_window(vars->vars.mlx, vars->vars.win);
	vars->vars.win = NULL;
	free_memory(vars->scene);
	exit (0);
}

static int	k_event(int keycode, t_data *vars)
{
	if (keycode == K_ESC)
		ft_close(vars);
	return (0);
}

void	my_hooks(t_data *vars)
{
	mlx_hook(vars->vars.win, 17, 1L << 17, &ft_close, vars);
	mlx_hook(vars->vars.win, 2, 1L << 0, &k_event, vars);
}
