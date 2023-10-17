/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:35:58 by adpachec          #+#    #+#             */
/*   Updated: 2023/10/17 15:44:15 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

static int	check_file_extension(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot && !ft_strcmp(dot, ".rt"))
		return (0);
	return (-1);
}

static void	change_tabs_for_spaces(char *line)
{
	int	i;

	i = -1;
	while ((line)[++i])
	{
		if ((line)[i] == '\t')
			(line)[i] = ' ';
	}
}

static int	end_msg(int error, t_scene **scene)
{
	if (error)
		return (error);
	if (!(*scene)->ambient.declared)
		return (AMBIENT_NOT_DECLARED);
	if (!(*scene)->camera.declared)
		return (CAMERA_NOT_DECLARED);
	if (!(*scene)->light.declared)
		return (LIGHT_NOT_DECLARED);
	return (SUCCESS);
}

/**
 * @brief Processes the input file to populate the scene structure.
 * 
 * This function reads the provided file line by line, parsing each line to
 * populate the scene structure. It checks for the correct file extension,
 * reads the file, and processes each line to extract scene information.
 * 
 * @param file The path to the input file.
 * @param scene A double pointer to the scene structure to be populated.
 * @param n A pointer to an integer that counts the number of processed lines.
 * 
 * @return An error code indicating the success or failure of the operation.
 *         Returns SUCCESS if the file is processed without errors.
 */

int	process_file(char *file, t_scene **scene, int *n)
{
	int			fd;
	int			error;
	char		*line;
	static char	*buf;

	if (check_file_extension(file) == -1)
		return (EXTENSION_E);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FILE_E);
	error = SUCCESS;
	line = get_next_line2(fd, &buf);
	while (line && !error)
	{
		(*n)++;
		change_tabs_for_spaces(line);
		error = parse_line(line, scene);
		if (line)
			free(line);
		if (!error)
			line = get_next_line2(fd, &buf);
	}
	free(buf);
	close(fd);
	return (end_msg(error, scene));
}
