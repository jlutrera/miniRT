/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:35:58 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/19 11:36:50 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/errors.h"

int is_normalized(t_vec vector)
{
	const double epsilon = 1e-10;
	double modulo;
    
	modulo = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    return fabs(modulo - 1.0) < epsilon;
}

double ft_atod(char *s)
{
	char	**aux;
	int		i;
	double	value;
	double	value2;

	aux = ft_split(s, '.');
	i = 0;
	while (aux[i])
		i++;
	if (i != 1 && i != 2)
		return 0;
	value = ft_atoi(aux[0]);
	if (aux[1])
		value2 = ft_atoi(aux[1]) / pow(10, ft_strlen2(aux[1]));
	i = -1;
	while (aux[++i])
		free(aux[i]);
	free(aux);
	if (value >= 0)
		return value + value2;
	return value - value2;
}

int ft_get_vector(char *s, t_vec *direction)
{
	char	**aux;
	int		i;
	double 	values[3];

	aux = ft_split(s, ',');
	i = -1;
	while (aux[++i])
	{
		values[i] = ft_atod(aux[i]);
		free(aux[i]);
	}
	free(aux);
	if (i != 3)
		return (-1);
	direction->x = values[0];
	direction->y = values[1];
	direction->z = values[2];
	return 0;
}

int ft_get_point(char *s, t_point3 *position)
{
	char	**aux;
	int		i;
	double 	values[3];

	aux = ft_split(s, ',');
	i = -1;
	while (aux[++i])
	{
		values[i] = ft_atod(aux[i]);
		free(aux[i]);
	}
	free(aux);
	if (i != 3)
		return (-1);
	position->x = values[0];
	position->y = values[1];
	position->z = values[2];
	return 0;
}

int ft_get_colour(char *s, t_color *color)
{
	char	**aux;
	int		i;
	int		error;
	int		values[3];

	aux = ft_split(s, ',');
	i = -1;
	error = 0;
	while (aux[++i])
	{
		values[i] = ft_atoi(aux[i]);
		if (values[i] < 0 || values[i] > 255)
			error = -1;
		free(aux[i]);
	}
	free(aux);
	if (i != 3 || error == -1)
		return -1;
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	return 0;
}

int ft_load_ambient(t_ambient *ambient, char **s)
{
	int		numcomponents;

	if (ambient->declared)
		return MORE_THAN_ONE_AMBIENT_E;
	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 3)
		return NUM_COMPONENTS_E;
	ambient->declared = true;
	ambient->ratio = ft_atod(s[1]);
	if (ambient->ratio < 0 || ambient->ratio > 1)
		return RATIO_E;
	if (ft_get_colour(s[2], &ambient->color) == -1)
		return COLOUR_E;
	return SUCCESS;
}

int ft_load_camera(t_camera *camera, char **s)
{
	int numcomponents;

	if (camera->declared)
		return MORE_THAN_ONE_CAMERA_E;
	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 4)
		return NUM_COMPONENTS_E;
	camera->declared = true;
	if (ft_get_point(s[1], &camera->position) ==  -1)
		return BAD_COORDINATES_E;
	camera->fov = ft_atoi(s[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return FOV_E;
	if (ft_get_vector(s[2], &camera->direction) == -1)
		return BAD_COORDINATES_E; 
	if (!is_normalized(camera->direction))
		return NORM_VECTOR_E;
	return SUCCESS;
}

int ft_load_light(t_light *light, char **s)
{
	int		numcomponents;

	if (light->declared)
		return MORE_THAN_ONE_LIGHT_E;
	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 4)
		return NUM_COMPONENTS_E;
	light->declared = true;
	if (ft_get_point(s[1], &light->position) ==  -1)
		return BAD_COORDINATES_E;
	light->bright = ft_atod(s[2]);
	if (light->bright < 0 || light->bright > 1)
		return BAD_BRIGHT_E;
	if (ft_get_colour(s[3], &light->color) == -1)
		return COLOUR_E;
	return SUCCESS;
}

int ft_load_spheres(t_scene *scene, char **s)
{
	int 		n;
	t_sphere 	*aux;
	int			numcomponents;

	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	printf("there are %i components\n", numcomponents);
	if (numcomponents != 4)
		return NUM_COMPONENTS_E;
	scene->nb_sp++;
	aux = ft_calloc(scene->nb_sp, sizeof(t_sphere));
	if (!aux)
		return MEMORY_E;
	n = -1;
	while (++n < scene->nb_sp - 1)
		aux[n] = scene->spheres[n];
	free(scene->spheres);
	scene->spheres = aux;
	scene->spheres[n].radius = ft_atod(s[2]) / 2;
	if (ft_get_point(s[1], &scene->spheres[n].center) == -1)
		return BAD_COORDINATES_E;
	if (scene->spheres[n].radius <= 0)
		return NEGATIVE_E;
	if (ft_get_colour(s[3], &scene->spheres[n].color) == -1)
		return COLOUR_E;
	return SUCCESS;
}

int ft_load_planes(t_scene *scene, char **s)
{
	int 		n;
	t_plane 	*aux;
	int			numcomponents;

	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 4)
		return NUM_COMPONENTS_E;
	scene->nb_pl++;
	aux = ft_calloc(scene->nb_pl, sizeof(t_sphere));
	if (!aux)
		return MEMORY_E;
	n = -1;
	while (++n < scene->nb_pl - 1)
		aux[n] = scene->planes[n];
	free(scene->planes);
	scene->planes = aux;
	if (ft_get_point(s[1], &scene->planes[n].coordenate) == -1 ||
		ft_get_vector(s[2], &scene->planes[n].direction) == -1)
		return BAD_COORDINATES_E;
	if (!is_normalized(scene->planes[n].direction))
		return NORM_VECTOR_E;
	if (ft_get_colour(s[3], &scene->planes[n].color) == -1)
		return COLOUR_E;
	return SUCCESS;
}

int check_cylinder(t_scene *scene, int n, char **s)
{
	if (ft_get_point(s[1], &scene->cylinders[n].coordenate) == -1 ||
		ft_get_vector(s[2], &scene->cylinders[n].direction) == -1)
		return BAD_COORDINATES_E;
	if (!is_normalized(scene->cylinders[n].direction))
		return NORM_VECTOR_E;
	if (scene->cylinders[n].radius <= 0 ||
		scene->cylinders[n].height <= 0)
		return NEGATIVE_E;
	if (ft_get_colour(s[5], &scene->cylinders[n].color) == -1)
		return COLOUR_E;
	return SUCCESS;
}

int ft_load_cylinders(t_scene *scene, char **s)
{
	int 		n;
	t_cylinder 	*aux;
	int			numcomponents;

	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 6)
		return NUM_COMPONENTS_E;
	scene->nb_cy++;
	aux = ft_calloc(scene->nb_cy, sizeof(t_sphere));
	if (!aux)
		return MEMORY_E;
	n = -1;
	while (++n < scene->nb_cy - 1)
		aux[n] = scene->cylinders[n];
	free(scene->cylinders);
	scene->cylinders = aux;
	scene->cylinders[n].radius = ft_atod(s[3]) / 2;
	scene->cylinders[n].height = ft_atod(s[4]);
	return check_cylinder(scene, n, s);
}

void ft_free_data(char **data, char *line_aux)
{
	int i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	free(line_aux);
}

int parse_line(char *line, t_scene *scene)
{
	char	**data;
	int		error;
	char	*line_aux;

	line_aux = ft_strtrim(line, " ");
	while (ft_strlen2(line_aux) > 1 && (line_aux[ft_strlen2(line_aux) - 1] == 13 || line_aux[ft_strlen2(line_aux) - 1] == 10))
		line_aux[ft_strlen2(line_aux) - 1] = '\0';	
	data = ft_split(line_aux, ' ');
	if (data[0][0] == 0 || data[0][0] == 13 || data[0][0] == 10)
		error = SUCCESS;
	else if (!ft_strcmp("A", data[0]))
		error = ft_load_ambient(&scene->ambient, data);
	else if (!ft_strcmp("C", data[0]))
		error = ft_load_camera(&scene->camera, data);
	else if (!ft_strcmp("L", data[0]))
		error = ft_load_light(&scene->light, data);
	else if (!ft_strcmp("sp", data[0]))
		error = ft_load_spheres(scene, data);
	else if (!ft_strcmp("pl", data[0]))
		error = ft_load_planes(scene, data);
	else if (!ft_strcmp("cy", data[0]))
		error = ft_load_cylinders(scene, data);
	else
		error = BAD_IDENTIFIER_E;
	ft_free_data(data, line_aux);
	return (error);
}

int check_file_extension(const char *filename)
{
	const char *dot;
	
	dot = ft_strrchr(filename, '.');

	if (dot && !ft_strcmp(dot, ".rt"))
		return 0;
	else
		return -1;
}

int	process_file(char *file, t_scene *scene, int *n)
{	
	int		fd;
	int		error;
	char	*line;

	if (check_file_extension(file) == -1)
        return EXTENSION_E;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FILE_E);
	error = SUCCESS;
	line = get_next_line(fd);
	while (line && !error)
	{
		(*n)++;
		error = parse_line(line, scene);
		free(line);
		if (!error)
			line = get_next_line(fd);
	}	
	close(fd);
	if (error)
		return (error);
	if (!scene->ambient.declared)
		return AMBIENT_NOT_DECLARED;
	if (!scene->camera.declared)
		return CAMERA_NOT_DECLARED;
	if (!scene->light.declared)
		return LIGHT_NOT_DECLARED;
	return (SUCCESS);
}
