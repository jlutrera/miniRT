/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:41:30 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/23 10:49:23 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*c_str;

	c_str = (unsigned char *)str;
	i = -1;
	while (++i < n)
		c_str[i] = (unsigned char)c;
	return (c_str);
}

/*
#include <string.h>
int main () {
   char str[50];

   strcpy(str,"Cadena original");
   puts(str);

   ft_memset(str,'$',23);
   puts(str);
   
   return(0);
}
*/