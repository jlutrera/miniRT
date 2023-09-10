/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:23:12 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/21 12:45:29 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*c_dest;
	unsigned char	*c_src;
	int				i;

	if (!dest && !src)
		return (0);
	i = -1;
	c_dest = (unsigned char *)dest;
	c_src = (unsigned char *)src;
	while (++i < (int)n)
		c_dest[i] = c_src[i];
	return (dest);
}
/*
#include <string.h>
int main () {
	int i = 0;
	//Source buffer
	int src[5] = {1,2,3,4,5};
	//dst buffer
	int dst[5] = {0};
	//copy source buffer int dst
	ft_memcpy(dst,src,sizeof(src));
	for(i=0; i<5; i++)
	{
		//printing dst buffer
		printf("%d ", dst[i]);
	}
   return(0);
}
*/