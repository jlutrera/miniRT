/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:29:17 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/09 12:23:48 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*dest;
	int		len_s1;
	int		len_total;
	int		i;

	len_s1 = ft_strlen2(s1);
	len_total = len_s1 + ft_strlen2(s2);
	if (len_total == 0)
	{
		free(s1);
		return (NULL);
	}
	dest = (char *)ft_calloc ((len_total + 1), sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		dest[i] = s1[i];
	--i;
	while (++i < len_total)
		dest[i] = s2[i - len_s1];
	dest[i] = '\0';
	free(s1);
	return (dest);
}
