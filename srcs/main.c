/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:42:53 by jutrera-          #+#    #+#             */
/*   Updated: 2023/09/20 18:44:30 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	ft_init(t_scene **scene)
{
	*scene = (t_scene *) malloc (sizeof(t_scene) * 1);
	if (!(*scene))
		exit (1);
	(*scene)->ambient.declared = false;
    (*scene)->camera.declared = false;
    (*scene)->light.declared = false;
    (*scene)->obj = NULL;
}

void free_memory(t_scene *scene)
{
	t_lst_obj *aux;
	
	if ((scene)->obj)
	{
		while (scene->obj)
		{
			aux = (scene)->obj;
			free(aux->object);
			free(aux);
			(scene)->obj = (scene)->obj->next;
		}	
	}
	free(scene);
}

void	print_scene(t_scene *scene)
{
	t_plane *plane;
	t_sphere *sphere;
	t_cylinder *cylinder;
	t_lst_obj *aux;
	
	if (!scene)
		exit (1);
	if (scene->ambient.declared)
	{
		printf("id: A\n");
		printf("   Ratio = %.4f", scene->ambient.ratio);
		printf("   Color = (%i, %i, %i)\n", scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	}
	if (scene->camera.declared)
	{
		printf("id: C\n");
		printf("   View point = (%.4f, %.4f, %.4f)", scene->camera.position.x, scene->camera.position.y, scene->camera.position.z );
		printf("   Orientation =(%.4f, %.4f, %.4f)", scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z );
		printf("   FOV = %i\n", scene->camera.fov);
	
	}
	if (scene->light.declared)
	{
		printf("id: L\n");
		printf("   Light point = (%.4f, %.4f, %.4f)", scene->light.position.x, scene->light.position.y, scene->light.position.z );
		printf("   Bright = %.4f", scene->light.bright);
		printf("   Color = (%i, %i, %i)\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	}
	aux = scene->obj;
	while (aux != NULL)
	{
		if (aux->type == PLANE)
		{
			plane = (t_plane *) aux->object;
			printf("id: pl\n");
			printf("   Coordenates: (%.4f, %.4f, %.4f)\n", plane->coordenate.x, plane->coordenate.y, plane->coordenate.z);
			printf("   Direction: (%.4f, %.4f, %.4f)\n", plane->direction.x, plane->direction.y, plane->direction.z);
			printf("   Color: (%d, %d, %d)\n", plane->color.r, plane->color.g, plane->color.b);
		}
		else if (aux->type == SPHERE)
		{
			sphere = (t_sphere *) aux->object;
			printf("id: sp\n");
			printf("   Center: (%.4f, %.4f, %.4f)\n", sphere->center.x, sphere->center.y, sphere->center.z);
			printf("   Radius: %.4f\n", sphere->radius);
			printf("   Color: (%d, %d, %d)\n", sphere->color.r, sphere->color.g, sphere->color.b);
		}
		else if (aux->type == CYLINDER)
		{
			cylinder = (t_cylinder *) aux->object;
			printf("id: cy\n");
			printf("   Coordenate: (%f, %f, %f)\n", cylinder->coordenate.x, cylinder->coordenate.y, cylinder->coordenate.z);
			printf("   Direction: (%f, %f, %f)\n", cylinder->direction.x, cylinder->direction.y, cylinder->direction.z);
			printf("   Radius: %f\n", cylinder->radius);
			printf("   Height: %f\n", cylinder->height);
			printf("   Color: (%d, %d, %d)\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
		}
		aux = aux->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene		*scene;
	int			error;
	int			n;

	if (argc != 2)
		return (ft_errormsg(SYNTAX_E, 0));
	ft_init(&scene);
	n = 0;
	error = process_file(argv[1], &scene, &n);
	if (error)
		return ft_errormsg(error, n);
	print_scene(scene);
	process_img(*scene);  //proceso la esfera
	free_memory(scene);
	return (SUCCESS);
}
