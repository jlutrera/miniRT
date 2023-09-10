/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:20:39 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/24 16:24:06 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != (unsigned char)c)
	{
		if (*str == 0)
			return (0);
		str++;
	}
	return (str);
}
/*
#include <stdio.h>
int main () {
   char str[] = "-100,0xff";
   char ch = ',';
   char *ret;

   ret = ft_strchr(str, ch);
   if (ret == 0)
		ret = "(null)";
   printf("String after |%c| is - |%s|\n", ch, ret);
   return(0);
}
*/