/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 23:17:48 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/09 12:44:43 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_findnl(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] != '\0')
		return (i);
	return (-1);
}

char	*ft_adjust_buff(char *s, int pos_nl, int i)
{
	int		j;
	char	*aux;
	int		len_s;

	if (!s || (pos_nl == -1 && i == 0))
		return (NULL);
	len_s = ft_strlen2(s);
	while (i < len_s)
		s[i++] = 0;
	if (pos_nl == -1)
		pos_nl = ft_strlen2(s);
	else
		++pos_nl;
	aux = (char *)ft_calloc(pos_nl + 1, sizeof(char));
	if (!aux)
		return (NULL);
	j = -1;
	while (++j < pos_nl)
		aux[j] = s[j];
	aux[j] = 0;
	return (aux);
}
