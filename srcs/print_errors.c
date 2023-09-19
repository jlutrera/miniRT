/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:34:23 by adpachec          #+#    #+#             */
/*   Updated: 2023/09/19 11:39:23 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/errors.h"

int	ft_errormsg(int e, int n)
{
	ft_printf("Error\n");
	if (e == FILE_E)
		ft_printf("It is not possible to open the file\n");
	else if (e == SYNTAX_E)
		ft_printf("Correct syntax: ./miniRT <file.rt>\n");
	else if (e == MORE_THAN_ONE_AMBIENT_E)
		ft_printf("There is more than one Ambient element\n");
	else if (e == MORE_THAN_ONE_CAMERA_E)
		ft_printf("There is more than one Camera element\n");
	else if (e == MORE_THAN_ONE_LIGHT_E)
		ft_printf("There is more than one Light element\n");
	else if (e == BAD_IDENTIFIER_E)
		ft_printf("Line %i has a bad identifier. Use A, C, L, sp, pl, cy\n", n);
	else if (e == AMBIENT_NOT_DECLARED)
		ft_printf("The Ambient element is not declared\n");
	else if (e == CAMERA_NOT_DECLARED)
		ft_printf("The Camera element is not declared\n");
	else if (e == LIGHT_NOT_DECLARED)
		ft_printf("The Light element is not declared\n");
	else if (e == NUM_COMPONENTS_E)
		ft_printf("Line %i has a bad number of components\n", n);
	else if (e == RATIO_E)
		ft_printf("Ratio number at line %i must be betwwen 0 and 1\n", n);
	else if (e == COLOUR_E)
		ft_printf("Bad colour number at line %i\n", n);
	else if (e == BAD_COORDINATES_E)
		ft_printf("Bad coordinates at line %i\n", n);
	else if (e == FOV_E)
		ft_printf("FOV number at line %i must be between 0 and 180\n", n);
	else if (e == NORM_VECTOR_E)
		ft_printf("The vector at line %i must be normalized\n", n);
	else if (e == BAD_BRIGHT_E)
		ft_printf("Bright number at line %i must be between 0 and 1\n", n);
	else if (e == MEMORY_E)
		ft_printf("Memory error\n");
	else if (e == NEGATIVE_E)
		ft_printf("Negative number at line %i\n", n);
	else if (e == EXTENSION_E)
		ft_printf("The file must have .rt extension\n");
	else
		ft_printf("Unknown error\n");
	return (e);
}
