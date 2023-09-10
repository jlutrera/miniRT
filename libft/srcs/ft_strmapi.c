/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:09:46 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 18:45:48 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_s;

	if (!s || !f)
		return (0);
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_s)
		return (0);
	i = 0;
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		++i;
	}
	new_s[i] = '\0';
	return (new_s);
}
/*
static char f(unsigned int i, char c)
{
	char str;
    
	str = c + 32;
	return (str);
}
int main()
{
	char str1[] = "ABCDEF";
	char* str2;
	str2 = ft_strmapi(str1, *f);
	printf("%s\n", str2);
}
*/