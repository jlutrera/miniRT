/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:20:39 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 18:46:25 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) + 1;
	while (--i >= 0)
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	return (0);
}

/*
#include <string.h>
int main () {
   char str[] = "-100,0xff";
   char ch = ',';
   char *ret;
   char *ret2;

   ret = ft_strrchr(str, ch);
   if (ret == 0)
		ret = "(null)";
   printf("My string after |%c| is -  %s \n", ch, ret);
   return(0);
}
*/