/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/15 20:53:39 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

static void	ft_free_data(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
		free(data[i]);
	free(data);
}

static bool	bad_line(char *line_aux)
{
	return (ft_strlen2(line_aux) > 1
		&& (line_aux[ft_strlen2(line_aux) - 1] == 13
			|| line_aux[ft_strlen2(line_aux) - 1] == 10));
}

static bool	data_is_empty(char **data)
{
	return (!data || !*data || data[0][0] == 0 ||
		data[0][0] == 13 || data[0][0] == 10);
}

static char	**load_data(char *line)
{
	char	*line_aux;
	char	**data;

	line_aux = ft_strtrim(line, " ");
	while (bad_line(line_aux))
		line_aux[ft_strlen2(line_aux) - 1] = '\0';
	data = ft_split(line_aux, ' ');
	free(line_aux);
	return (data);
}

int	parse_line(char *line, t_scene **scene)
{
	char	**data;
	int		error;

	data = load_data(line);
	if (data_is_empty(data))
		error = SUCCESS;
	else if (!ft_strcmp("A", data[0]))
		error = ft_load_ambient(&(*scene)->ambient, data);
	else if (!ft_strcmp("C", data[0]))
		error = ft_load_camera(&(*scene)->camera, data);
	else if (!ft_strcmp("L", data[0]))
		error = ft_load_light(&(*scene)->light, data);
	else if (!ft_strcmp("sp", data[0]))
		error = ft_load_sp(&((*scene)->obj), data);
	else if (!ft_strcmp("pl", data[0]))
		error = ft_load_pl(&((*scene)->obj), data);
	else if (!ft_strcmp("cy", data[0]))
		error = ft_load_cy(&((*scene)->obj), data);
	else if (!ft_strcmp("tr", data[0]))
		error = ft_load_tr(&((*scene)->obj), data);
	else if (!ft_strcmp("co", data[0]))
		error = ft_load_co(&((*scene)->obj), data);
	else
		error = BAD_IDENTIFIER_E;
	return (ft_free_data(data), error);
}
