/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_gets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:40:34 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/06 18:44:55 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT_bonus.h"

int	ft_get_vector(char *s, t_vec *direction)
{
	char	**aux;
	int		i;
	double	values[3];

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
	return (0);
}

int	ft_get_point(char *s, t_point3 *position)
{
	char	**aux;
	int		i;
	double	values[3];

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
	return (0);
}

int	ft_get_color(char *s, t_color *color)
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
		return (-1);
	*color = (t_color){values[0], values[1], values[2]};
	if (color->r == 0 && color->g == 0 && color->b == 0)
		*color = (t_color){30, 30, 30};
	return (0);
}
