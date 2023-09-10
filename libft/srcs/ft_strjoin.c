/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:43:08 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 18:44:23 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (0);
	if (!s2 && s1)
		return ((char *)s1);
	if (!s1 && s2)
		return ((char *)s2);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = (char *)malloc ((len_s1 + len_s2 + 1) * sizeof(char));
	if (!dest)
		return (0);
	ft_memcpy(dest, s1, len_s1);
	ft_memcpy(dest + len_s1, s2, len_s2);
	dest[len_s1 + len_s2] = 0;
	return (dest);
}	

/*
int main()
{
	char s1[] = "Look Here";
	char s2[] = " Unimaginable";
	char *dest;

	dest = (char *)malloc(100);
	dest = ft_strjoin(s1, s2);
	printf("%s", dest);

	return 0;
}
*/