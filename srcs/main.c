/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:42:53 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/09 19:26:17 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static void	ft_init(t_scene **scene)
{
	*scene = (t_scene *) malloc (sizeof(t_scene) * 1);
	if (!(*scene))
		exit (1);
	(*scene)->ambient.declared = false;
	(*scene)->camera.declared = false;
	(*scene)->light.declared = false;
	(*scene)->obj = NULL;
}

void	free_memory(t_scene *scene)
{
	t_lst_obj	*aux;

	if ((scene)->obj)
	{
		while (scene->obj)
		{
			aux = (scene)->obj;
			(scene)->obj = (scene)->obj->next;
			free(aux->object);
			free(aux);
		}
	}
	free(scene);
}

static void	init_mlx(t_data *data, t_scene *scene)
{
	data->image.width = WIDTH;
	data->image.height = floor(data->image.width / (ASPECT_RATIO));
	if (data->image.height < 1)
		data->image.height = 1;
	data->vars.mlx = mlx_init();
	data->vars.win = mlx_new_window(data->vars.mlx, data->image.width,
			data->image.height, "miniRT");
	data->image.img = mlx_new_image(data->vars.mlx, data->image.width,
			data->image.height);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel, &data->image.line_length,
			&data->image.endian);
	data->scene = scene;
}

void	ft_leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_scene		*scene;
	int			error;
	int			n;

	atexit(ft_leaks);
	if (argc != 2)
		return (ft_errormsg(SYNTAX_E, 0));
	if (WIDTH <= 0)
		return (ft_printf("Bad resolution !\n"), 0);
	ft_init(&scene);
	n = 0;
	error = process_file(argv[1], &scene, &n);
	if (error)
	{
		free_memory(scene);
		return (ft_errormsg(error, n));
	}
	init_mlx(&data, scene);
	process_img(&data, scene);
	ft_printf("END RENDER\n");
	my_hooks(&data);
	mlx_loop(data.vars.mlx);
	return (SUCCESS);
}
