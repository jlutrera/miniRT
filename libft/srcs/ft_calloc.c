/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:11:43 by jutrera-          #+#    #+#             */
/*   Updated: 2023/10/09 12:33:28 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			n;
	size_t			i;
	unsigned char	*p;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	p = (unsigned char *)malloc (count * size);
	if (!p)
		return (NULL);
	n = size * count;
	i = -1;
	while (++i < n)
		p[i] = '\0';
	return (p);
}
