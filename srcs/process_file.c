/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:35:58 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/19 13:38:27 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	ft_get_dist(void)
{
	return (0.0);
}

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

int check_comps(char **s, int n)
{
	int i;

	i = -1;
	while (s[++i]);
	if (i != n)
		return 1;
	return 0;
}

int ft_load_ambient(t_ambient *ambient, char **s)
{	
	if (ambient->declared)
		return MORE_THAN_ONE_AMBIENT_E;
	if (check_comps(s, 3))
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
	if (camera->declared)
		return MORE_THAN_ONE_CAMERA_E;
	if (check_comps(s, 4))
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
	if (light->declared)
		return MORE_THAN_ONE_LIGHT_E;
	if (check_comps(s, 4))
		return (NUM_COMPONENTS_E);
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

t_lst_obj	*ft_init_obj(void *object, t_obj_type type, double last_dist)
{
	t_lst_obj	*new_obj;

	//probablemente forzar tipo de dato segun type:
	//if (type == SPHERE)
	//new_obj->object = (t_sphere *) object;
	new_obj = malloc(sizeof(t_lst_obj));
	if (!new_obj)
		return NULL;
	new_obj->object = object;
	new_obj->type = type;
	new_obj->last_dist = last_dist;
	new_obj->skip = 0;
	new_obj->next = NULL;
	return (new_obj);
}

t_lst_obj *ft_obj_last(t_lst_obj *obj)
{
	t_lst_obj	*aux;

	aux = obj;
	if (!aux)
		return (NULL);
	while(aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	ft_add_back_obj(t_lst_obj **obj, void *object, t_obj_type type,	double last_dist)
{
	t_lst_obj	*new_obj;
	t_lst_obj	*aux;

	new_obj = ft_init_obj(object, type, last_dist);
	if (new_obj) 
	{
		if (!(*obj))
			*obj = new_obj;
		else
		{
			aux = ft_obj_last(*obj);
			if (!aux)
				*obj = new_obj;
			else
				aux->next = new_obj;
		}
	}
}

t_sphere	*new_sphere(char **s, int *e)
{
	t_sphere	*new_sp;

	new_sp = ft_calloc(sizeof(t_sphere *), 1);
	if (!new_sp)
	{
		*e = MEMORY_E;
		return NULL;
	}
	new_sp->radius = ft_atod(s[2]) / 2;
	if (ft_get_point(s[1], &new_sp->center) == -1)
	{
		free(new_sp);
		*e = BAD_COORDINATES_E;
		return NULL;
	}
	if (new_sp->radius <= 0)
	{
		free(new_sp);
		*e = NEGATIVE_E;
		return NULL;
	}
	if (ft_get_colour(s[3], &new_sp->color) == -1)
	{	
		free(new_sp);
		*e = COLOUR_E;
		return NULL;
	}
	return (new_sp);
}

int ft_load_spheres(t_scene *scene, char **s)
{
	int			e;
	t_sphere	*new_sp;

	if (check_comps(s, 4))
		return NUM_COMPONENTS_E;
	new_sp = new_sphere(s, &e);
	if (!new_sp)
		return e;
	ft_add_back_obj(&(scene->obj), new_sp, SPHERE, ft_get_dist());
	return (SUCCESS);
}

t_plane	*new_plane(char **s, int *e)
{
	t_plane	*new_pl;

	new_pl = ft_calloc(sizeof(t_plane *), 1);
	if (!new_pl)
	{
		*e = MEMORY_E;		
		return NULL;
	}
	if (ft_get_point(s[1], &new_pl->coordenate) == -1 ||
		ft_get_vector(s[2], &new_pl->direction) == -1)
	{
		free(new_pl);
		*e = BAD_COORDINATES_E;
		return NULL;
	}
	if (!is_normalized(new_pl->direction))
	{
		free(new_pl);
		*e = NORM_VECTOR_E;
		return NULL;
	}
	if (ft_get_colour(s[3], &new_pl->color) == -1)
	{
		free(new_pl);
		*e = COLOUR_E;
		return NULL;
	}
	return (new_pl);
}

int	ft_load_planes(t_scene *scene, char **s)
{
	int			e;
	t_plane		*new_pl;

	if (check_comps(s, 4))
		return NUM_COMPONENTS_E;
	new_pl = new_plane(s, &e);
	if (!new_pl)
		return e;
	ft_add_back_obj(&(scene->obj), new_pl, PLANE, ft_get_dist());
	return SUCCESS;
}

t_cylinder	*new_cylinder(char **s, int *e)
{
	t_cylinder	*new_cy;

	new_cy = ft_calloc(sizeof(t_cylinder *), 1);
	if (!new_cy)
	{
		*e = MEMORY_E;
		return NULL;
	}
	new_cy->radius = ft_atod(s[3]) / 2;
	new_cy->height = ft_atod(s[4]);
	if (ft_get_point(s[1], &new_cy->coordenate) == -1 ||
		ft_get_vector(s[2], &new_cy->direction) == -1)
	{
		free(new_cy);
		*e = BAD_COORDINATES_E;
		return NULL;
	}
	if (!is_normalized(new_cy->direction))
	{
		free(new_cy);
		*e = NORM_VECTOR_E;
		return NULL;
	}
	if (new_cy->radius <= 0 || new_cy->height <= 0)
	{
		free(new_cy);
		*e = NEGATIVE_E;
		return NULL;
	}
	if (ft_get_colour(s[5], &new_cy->color) == -1)
	{
		free(new_cy);
		*e = COLOUR_E;
		return NULL;
	}
	return (new_cy);
}

int ft_load_cylinders(t_scene *scene, char **s)
{
	int			e;
	t_cylinder	*new_cy;

	if (check_comps(s, 6))
		return NUM_COMPONENTS_E;
	new_cy = new_cylinder(s, &e);
	if (!new_cy)
		return e;
	ft_add_back_obj(&(scene->obj), new_cy,	CYLINDER, ft_get_dist());
	return SUCCESS;
}

void ft_free_data(char **data, t_scene *scene)
{
	int 	i;
	void	*aux;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	while (scene->obj)
	{
		aux = scene->obj;
		free(scene->obj->object);
		scene->obj = scene->obj->next;
		free(aux);
	}
	free(scene->obj);
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
	ft_free_data(data, scene);
	free(line_aux);
	return (error);
}

int check_file_extension(const char *filename)
{
	const char *dot;
	
	dot = ft_strrchr(filename, '.');
	if (dot && !ft_strcmp(dot, ".rt"))
		return 0;
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
