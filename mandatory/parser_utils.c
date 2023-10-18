/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:51:27 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/18 18:25:03 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

double	ft_get_dist(void)
{
	return (0.0);
}

int	is_normalized(t_vec vector)
{
	if (vector.x > 1 || vector.x < -1)
		return (0);
	else if (vector.y > 1 || vector.y < -1)
		return (0);
	else if (vector.z > 1 || vector.z < -1)
		return (0);
	return (1);
}

double	ft_atod(char *s)
{
	char	**aux;
	int		i;
	double	value;
	double	value2;
	int		sign;	

	aux = ft_split(s, '.');
	if (!aux)
		exit (1);
	i = 0;
	while (aux[i])
		i++;
	if (i != 1 && i != 2)
		return (ft_free(aux), 0);
	sign = 1;
	if (aux[0][0] == '-')
		sign = -1;
	value = ft_atol(aux[0]);
	value2 = 0;
	if (aux[1])
		value2 = ft_atol(aux[1]) / pow(10, ft_strlen2(aux[1]));
	return (ft_free(aux), value + value2 * sign);
}

int	check_comps(char **s, int n)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	if (i != n)
		return (1);
	return (0);
}
