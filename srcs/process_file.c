#include "../include/miniRT.h"


int is_normalized(t_point3d point)
{
	const float epsilon = 1e-10;
	float modulo;
    
	modulo = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
    return fabs(modulo - 1.0) < epsilon;
}

float ft_atofl(char *s)
{
	char	**aux;
	int		i;
	float	value;
	float	value2;

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

int ft_get_point(char *s, t_point3d *position)
{
	char	**aux;
	int		i;
	float 	values[3];

	aux = ft_split(s, ',');
	i = -1;
	while (aux[++i])
	{
		values[i] = ft_atofl(aux[i]);
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

int ft_get_colour(char *s, t_colour *colours)
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
	colours->r = values[0];
	colours->g = values[1];
	colours->b = values[2];
	return 0;
}

int ft_load_ambient(t_ambient *ambient, char **s)
{
	int		numcomponents;

	if (ambient->declared)
		return 2;
	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 3)
		return 8;
	ambient->declared = true;
	ambient->ratio = ft_atofl(s[1]);
	if (ambient->ratio < 0 || ambient->ratio > 1)
		return 8;
	if (ft_get_colour(s[2], &ambient->colour) == -1)
		return 8;
	return 0;
}

int ft_load_camera(t_camera *camera, char **s)
{
	int numcomponents;

	if (camera->declared)
		return 3;
	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 4)
		return 8;
	camera->declared = true;
	if (ft_get_point(s[1], &camera->position) ==  -1)
		return 8;
	camera->fov = ft_atoi(s[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return 8;
	if (ft_get_point(s[2], &camera->direction) == -1 || !is_normalized(camera->direction))
		return 8;
	return 0;
}

int ft_load_light(t_light *light, char **s)
{
	int		numcomponents;

	if (light->declared)
		return 4;
	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 4)
		return 8;
	light->declared = true;
	if (ft_get_point(s[1], &light->position) ==  -1)
		return 8;
	light->bright = ft_atofl(s[2]);
	if (light->bright < 0 || light->bright > 1)
		return 8;
	if (ft_get_colour(s[3], &light->colour) == -1)
		return 8;
	return 0;
}

int ft_load_spheres(t_scene *scene, char **s)
{
	int 		n;
	t_sphere 	*aux;
	int			numcomponents;

	numcomponents = 0;
	while (s[numcomponents])
		numcomponents++;
	if (numcomponents != 4)
		return 8;
	scene->nb_sp++;
	aux = ft_calloc(scene->nb_sp, sizeof(t_sphere));
	if (!aux)
		return 8;
	n = -1;
	while (++n < scene->nb_sp - 1)
		aux[n] = scene->spheres[n];
	free(scene->spheres);
	scene->spheres = aux;
	scene->spheres[n].radius = ft_atofl(s[2]) / 2;
	if (ft_get_point(s[1], &scene->spheres[n].center) == -1 ||
		scene->spheres[n].radius <= 0 ||
		ft_get_colour(s[3], &scene->spheres[n].colour) == -1)
		return 8;
	return 0;
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
		return 8;
	scene->nb_pl++;
	aux = ft_calloc(scene->nb_pl, sizeof(t_sphere));
	if (!aux)
		return 8;
	n = -1;
	while (++n < scene->nb_pl - 1)
		aux[n] = scene->planes[n];
	free(scene->planes);
	scene->planes = aux;
	if (ft_get_point(s[1], &scene->planes[n].coordenate) == -1 ||
		ft_get_point(s[2], &scene->planes[n].direction) == -1 ||
		!is_normalized(scene->planes[n].direction) ||
		ft_get_colour(s[3], &scene->planes[n].colour) == -1)
		return 8;
	return 0;
}

int check_cylinder(t_scene *scene, int n, char **s)
{
	if (ft_get_point(s[1], &scene->cylinders[n].coordenate) == -1 ||
		ft_get_point(s[2], &scene->cylinders[n].direction) == -1 ||
		!is_normalized(scene->cylinders[n].direction) ||
		scene->cylinders[n].radius <= 0 ||
		scene->cylinders[n].height <= 0 ||
		ft_get_colour(s[5], &scene->cylinders[n].colour) == -1)
		return 8;
	return 0;
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
		return 8;
	scene->nb_cy++;
	aux = ft_calloc(scene->nb_cy, sizeof(t_sphere));
	if (!aux)
		return 8;
	n = -1;
	while (++n < scene->nb_cy - 1)
		aux[n] = scene->cylinders[n];
	free(scene->cylinders);
	scene->cylinders = aux;
	scene->cylinders[n].radius = ft_atofl(s[3]) / 2;
	scene->cylinders[n].height = ft_atofl(s[4]);
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
	data = ft_split(line_aux, ' ');
	if (data[0][0] == 13)
		error = 0;
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
		error = 8;
	ft_free_data(data, line_aux);
	return (error);
}

int	process_file(char *file, t_scene *scene)
{	
	int		fd;
	int		error;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	error = 0;
	line = get_next_line(fd);
	while (line && !error)
	{
		error = parse_line(line, scene);
		free(line);
		if (!error)
			line = get_next_line(fd);
	}	
	close(fd);
	if (!scene->ambient.declared || !scene->camera.declared || ! scene->light.declared)
		return 8;
	return (error);
}
