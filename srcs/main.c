/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:42:53 by jutrera-          #+#    #+#             */
/*   Updated: 2023/09/20 18:43:30 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

// void printvalores(t_scene scene)
// {
// 	int n;

// 	if (scene.ambient.declared)
// 	{
// 		printf("id: A");
// 		printf("   ratio = %.4f", scene.ambient.ratio);
// 		printf("   color = (%i,%i,%i)\n", scene.ambient.color.r, scene.ambient.color.g, scene.ambient.color.b);
// 	}
// 	if (scene.camera.declared)
// 	{
// 		printf("id: C");
// 		printf("   view point = (%.4f,%.4f,%.4f)", scene.camera.position.x, scene.camera.position.y, scene.camera.position.z );
// 		printf("   orientation =(%.4f,%.4f,%.4f)", scene.camera.direction.x, scene.camera.direction.y, scene.camera.direction.z );
// 		printf("   FOV = %i\n", scene.camera.fov);
	
// 	}
// 	if (scene.light.declared)
// 	{
// 		printf("id: L");
// 		printf("   light point = (%.4f,%.4f,%.4f)", scene.light.position.x, scene.light.position.y, scene.light.position.z );
// 		printf("   bright = %.1f", scene.light.bright);
// 		printf("   color = (%i,%i,%i)\n", scene.light.color.r, scene.light.color.g, scene.light.color.b);
// 	}
// 	n = 0;
// 	while (n < scene.nb_sp)
// 	{
// 		printf("id: sp [%i]", n);
// 		printf("   center = (%.4f,%.4f,%.4f)", scene.spheres[n].center.x, scene.spheres[n].center.y, scene.spheres[n].center.z);
// 		printf("   radius = %.4f", scene.spheres[n].radius);
// 		printf("   color = (%i,%i,%i)\n", scene.spheres[n].color.r, scene.spheres[n].color.g, scene.spheres[n].color.b);
// 		printf("\n");
// 		n++;
// 	}
// 	n = 0;
// 	while (n < scene.nb_pl)
// 	{
// 		printf("id: pl [%i]", n);
// 		printf("   coordinates = (%.4f,%.4f,%.4f)", scene.planes[n].coordenate.x, scene.planes[n].coordenate.y, scene.planes[n].coordenate.z);
// 		printf("   direction =(%.4f,%.4f,%.4f)", scene.planes[n].direction.x, scene.planes[n].direction.y, scene.planes[n].direction.z );
// 		printf("   color = (%i,%i,%i)\n", scene.planes[n].color.r, scene.planes[n].color.g, scene.planes[n].color.b);
// 		printf("\n");
// 		n++;
// 	}
// 	n = 0;
// 	while (n < scene.nb_cy)
// 	{
// 		printf("id: cy [%i]", n);
// 		printf("   coordinates = (%.4f,%.4f,%.4f)", scene.cylinders[n].coordenate.x, scene.cylinders[n].coordenate.y, scene.cylinders[n].coordenate.z);
// 		printf("   direction =(%.4f,%.4f,%.4f)", scene.cylinders[n].direction.x, scene.cylinders[n].direction.y, scene.cylinders[n].direction.z );
// 		printf("   radius = %.4f", scene.cylinders[n].radius);
// 		printf("   height = %.4f", scene.cylinders[n].height);
// 		printf("   color = (%i,%i,%i)\n", scene.cylinders[n].color.r, scene.cylinders[n].color.g, scene.cylinders[n].color.b);
// 		printf("\n");
// 		n++;
// 	}
// }

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

void ft_free_memory(t_scene *scene)
{
	t_lst_obj *aux;
	
	printf("voy a free: %p\n", (scene)->obj);
	if ((scene)->obj)
	{
		printf("dentro free\n");
		while (scene->obj)
		{
			aux = (scene)->obj;
			free(aux->object);
			free(aux);
			(scene)->obj = (scene)->obj->next;
			printf("elimino\n");
		}	
	}
	free(scene);
}

void	ft_print_scene(t_scene *scene)
{
	t_plane *plane;
	t_sphere *sphere;
	t_cylinder *cylinder;
	t_lst_obj *aux;
	
	if (!scene)
		exit (1);
	// if (scene->ambient.declared)
	// {
	// 	printf("id: A");
	// 	printf("   ratio = %.4f", scene->ambient.ratio);
	// 	printf("   color = (%i,%i,%i)\n", scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	// }
	// if (scene->camera.declared)
	// {
	// 	printf("id: C");
	// 	printf("   view point = (%.4f,%.4f,%.4f)", scene->camera.position.x, scene->camera.position.y, scene->camera.position.z );
	// 	printf("   orientation =(%.4f,%.4f,%.4f)", scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z );
	// 	printf("   FOV = %i\n", scene->camera.fov);
	
	// }
	// if (scene->light.declared)
	// {
	// 	printf("id: L");
	// 	printf("   light point = (%.4f,%.4f,%.4f)", scene->light.position.x, scene->light.position.y, scene->light.position.z );
	// 	printf("   bright = %.1f", scene->light.bright);
	// 	printf("   color = (%i,%i,%i)\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	// }
	aux = scene->obj;
	while (aux != NULL)
	{
		printf("Type: %d\n", aux->type);
		if (aux->type == PLANE)
		{
			plane = (t_plane *) aux->object;
			printf("Coordenates: %f %f %f\n", plane->coordenate.x, plane->coordenate.y, plane->coordenate.z);
			printf("Direction: %f %f %f\n", plane->direction.x, plane->direction.y, plane->direction.z);
			printf("Color: %d %d %d\n", plane->color.r, plane->color.g, plane->color.b);
		}
		else if (aux->type == SPHERE)
		{
			sphere = (t_sphere *) aux->object;
			printf("Center: %f %f %f\n", sphere->center.x, sphere->center.y, sphere->center.z);
			printf("Radius: %f\n", sphere->radius);
			printf("Color: %d %d %d\n", sphere->color.r, sphere->color.g, sphere->color.b);
		}
		else if (aux->type == CYLINDER)
		{
			cylinder = (t_cylinder *) aux->object;
			printf("Coordenate: %f %f %f\n", cylinder->coordenate.x, cylinder->coordenate.y, cylinder->coordenate.z);
			printf("Direction: %f %f %f\n", cylinder->direction.x, cylinder->direction.y, cylinder->direction.z);
			printf("Radius: %f\n", cylinder->radius);
			printf("Height: %f\n", cylinder->height);
			printf("Color: %d %d %d\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
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
	ft_print_scene(scene);
	ft_free_memory(scene);
	//process_planes(scene, argv[1]);
	//process_spheres(scene, argv[1]);
	//process_cylinders(scene, argv[1]);
	// return ft_free_memory(&scene), ft_errormsg(error, n);
	return (SUCCESS);
}
