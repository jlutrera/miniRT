/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:43:57 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 18:46:09 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n_len;

	if (!haystack && len == 0)
		return (0);
	n_len = ft_strlen(needle);
	if (n_len == 0)
		return ((char *)haystack);
	i = 0;
	while ((haystack[i] != '\0') && ((n_len + i) <= len))
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (++j < n_len)
				if (haystack[i + j] != needle[j])
					j = n_len + 1;
			if (j == n_len)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (0);
}
