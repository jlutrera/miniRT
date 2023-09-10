/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:59:50 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 18:46:57 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (s1 && set)
	{
		start = 0;
		while (s1[start] && ft_char_in_set(s1[start], set))
			start++;
		end = ft_strlen(s1);
		while (end > start && ft_char_in_set(s1[end - 1], set))
			end--;
		len = end - start;
		return (ft_substr(s1, start, len));
	}
	else
		return (0);
}
/*
int main()
{
	char *texto = "xxx  xxx      xHola esto es una pruebax   xx    xxxxx";

	printf("Resultado de ft_strtrim = %s", ft_strtrim(texto, "x"));
}
*/