/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 23:17:58 by jutrera-          #+#    #+#             */
/*   Updated: 2023/02/25 01:31:17 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_remain_buff(char *s, int pos_nl, int i)
{
	int		j;
	int		len;
	char	*aux;

	if (!s || pos_nl == -1 || i == -1)
		return (NULL);
	len = ft_strlen2(s);
	aux = (char *)ft_calloc((len - pos_nl), sizeof(char));
	if (!aux)
		return (NULL);
	j = 0;
	while (j < len - pos_nl - 1)
	{
		aux[j] = s[pos_nl + j + 1];
		j++;
	}
	aux[j] = 0;
	return (aux);
}

char	*ft_read_line(char *buff, char *str, int pos_nl, int i)
{
	char	*line;
	char	*aux;

	if (i == -1)
		return (NULL);
	aux = ft_adjust_buff(str, pos_nl, i);
	line = ft_strjoin2(buff, aux);
	free(aux);
	return (line);
}

char	*ft_init_str(int fd, char *buff, int *pos_nl)
{
	char	*str;

	if (fd == -1 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(buff);
		return (NULL);
	}
	*pos_nl = ft_findnl(buff);
	if (*pos_nl == -1)
		str = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	else
		str = ft_strjoin2(buff, NULL);
	return (str);
}

int	ft_init_i(int fd, char *str, int *pos_nl)
{
	int	i;

	if (*pos_nl == -1)
	{
		i = read(fd, str, BUFFER_SIZE);
		*pos_nl = ft_findnl(str);
	}
	else
		i = ft_strlen2(str);
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*str;
	char		*line;
	int			pos_nl;
	int			i;

	pos_nl = 0;
	str = ft_init_str(fd, buff, &pos_nl);
	if (!str || pos_nl != -1)
		buff = NULL;
	i = ft_init_i(fd, str, &pos_nl);
	while (i == BUFFER_SIZE && pos_nl == -1)
	{
		buff = ft_strjoin2(buff, str);
		i = read(fd, str, BUFFER_SIZE);
		pos_nl = ft_findnl(str);
	}
	line = ft_read_line(buff, str, pos_nl, i);
	buff = ft_remain_buff(str, pos_nl, i);
	if (buff == 0 || i == -1)
		free(buff);
	free(str);
	return (line);
}
