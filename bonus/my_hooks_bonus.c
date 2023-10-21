/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:52:42 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/21 11:18:03 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static void	reload_img(t_data *data)
{
	mlx_destroy_image(data->vars.mlx, data->image.img);
	data->image.img = mlx_new_image(data->vars.mlx, data->image.width,
			data->image.height);
	if (!data->image.img)
		exit (1);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel, &data->image.line_length,
			&data->image.endian);
	if (!data->image.addr)
		exit (1);
	process_img(data, data->scene);
}

static void	ft_other_camera(int dir, t_data *data)
{
	t_camera	*cam;
	t_camera	*tmp_prev;

	cam = data->scene->camera;
	tmp_prev = NULL;
	while (!cam->active)
	{
		tmp_prev = cam;
		cam = cam->next;
	}
	if (dir == 1 && cam->next)
	{
		cam->next->active = 1;
		cam->active = 0;
		reload_img(data);
	}
	if (dir == -1 && tmp_prev)
	{
		tmp_prev->active = 1;
		cam->active = 0;
		reload_img(data);
	}
}

static int	ft_close(t_data *data)
{
	mlx_destroy_image(data->vars.mlx, data->image.img);
	mlx_destroy_window(data->vars.mlx, data->vars.win);
	data->vars.win = NULL;
	free_memory(data->scene);
	exit (0);
}

static int	k_event(int keycode, t_data *data)
{
	if (keycode == K_ESC)
		ft_close(data);
	else if (keycode == K_RIGHT)
		ft_other_camera(1, data);
	else if (keycode == K_LEFT)
		ft_other_camera(-1, data);
	return (0);
}

void	my_hooks(t_data *data)
{
	mlx_hook(data->vars.win, 17, 1L << 17, &ft_close, data);
	mlx_hook(data->vars.win, 2, 1L << 0, &k_event, data);
}
