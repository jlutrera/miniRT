/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 18:56:13 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static void	ft_free_data(char **data, char	*line_aux)
{
	int	i;

	i = -1;
	while (data[++i])
		free(data[i]);
	free(data);
	free(line_aux);
}

static bool	bad_line(char *line_aux)
{
	return (ft_strlen2(line_aux) > 1
		&& (line_aux[ft_strlen2(line_aux) - 1] == 13
			|| line_aux[ft_strlen2(line_aux) - 1] == 10));
}

int	parse_line(char *line, t_scene **scene)
{
	char	**data;
	int		error;
	char	*line_aux;

	line_aux = ft_strtrim(line, " ");
	while (bad_line(line_aux))
		line_aux[ft_strlen2(line_aux) - 1] = '\0';
	data = ft_split(line_aux, ' ');
	if (data[0][0] == 0 || data[0][0] == 13 || data[0][0] == 10)
		error = SUCCESS;
	else if (!ft_strcmp("A", data[0]))
		error = ft_load_ambient(&(*scene)->ambient, data);
	else if (!ft_strcmp("C", data[0]))
		error = ft_load_camera(&(*scene)->camera, data);
	else if (!ft_strcmp("L", data[0]))
		error = ft_load_light(&(*scene)->light, data);
	else if (!ft_strcmp("sp", data[0]))
		error = ft_load_spheres(&((*scene)->obj), data);
	else if (!ft_strcmp("pl", data[0]))
		error = ft_load_planes(&((*scene)->obj), data);
	else if (!ft_strcmp("cy", data[0]))
		error = ft_load_cylinders(&((*scene)->obj), data);
	else
		error = BAD_IDENTIFIER_E;
	return (ft_free_data(data, line_aux), error);
}
