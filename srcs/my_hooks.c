/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:52:42 by jutrera-          #+#    #+#             */
/*   Updated: 2023/02/09 09:52:42 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static int	ft_close(t_vars *vars)
{
	mlx_destroy_window((*vars).mlx, (*vars).win);
	(*vars).win = NULL;
	exit (0);
}

static int	k_event(int keycode, t_vars *vars)
{
	if (keycode == K_ESC)
		ft_close(vars);
/*
	else if (keycode == K_RIGHT)
	//	ft_translate(10, 0, vars);
	else if (keycode == K_LEFT)
	//	ft_translate(-10, 0, vars);
	else if (keycode == K_DOWN)
	//	ft_translate(0, 10, vars);
	else if (keycode == K_UP)
	//	ft_translate(0, -10, vars);
	else if (keycode == K_A)
	//	ft_zoom(1.02, vars);
	else if (keycode == K_D)
	//	ft_zoom(0.98, vars);
	else if (keycode == K_S)
	//	ft_rotate(-0.05, vars);
	else if (keycode == K_W)
	//	ft_rotate(0.05, vars);
*/
	return (0);
}
/*
static int	mouse_press(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == M_B_L)
		(*vars).mouse.is_pressedl = 1;
	else if (button == M_B_R)
		(*vars).mouse.is_pressedr = 1;
	else if (button == M_B_CDOWN)
	//	ft_zoom(1.02, vars);
	else if (button == M_B_CUP)
	//	ft_zoom(0.98, vars);
	return (0);
}

static int	mouse_release(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == M_B_L)
		(*vars).mouse.is_pressedl = 0;
	else if (button == M_B_R)
		(*vars).mouse.is_pressedr = 0;
	return (0);
}

static int	mouse_move(int x, int y, t_vars *vars)
{
	int	delta_x;
	int	delta_y;

	(*vars).mouse.prev_x = (*vars).mouse.x;
	(*vars).mouse.prev_y = (*vars).mouse.y;
	(*vars).mouse.x = x;
	(*vars).mouse.y = y;
	delta_x = (*vars).mouse.x - (*vars).mouse.prev_x;
	delta_y = (*vars).mouse.y - (*vars).mouse.prev_y;
	if ((*vars).mouse.is_pressedl)
		//ft_translate(delta_x, delta_y, vars);
	else if ((*vars).mouse.is_pressedr)
	{
		if (delta_y > 0)
		//	ft_rotate(1, vars);
		else if (delta_y < 0)
		//	ft_rotate(-1, vars);
	}
	return (0);
}
*/
void	my_hooks(t_vars *vars)
{
	mlx_hook((*vars).win, 17, 1L << 17, &ft_close, vars);
	mlx_hook((*vars).win, 2, 1L << 0, &k_event, vars);
//	mlx_hook((*vars).win, 4, 1L << 2, &mouse_press, vars);
//	mlx_hook((*vars).win, 5, 1L << 3, &mouse_release, vars);
//	mlx_hook((*vars).win, 6, 1L << 6, &mouse_move, vars);
}
