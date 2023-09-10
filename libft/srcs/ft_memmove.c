/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:23:12 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 18:41:08 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*to;
	unsigned char	*from;
	int				i;

	to = (unsigned char *)dest;
	from = (unsigned char *)src;
	if (from == to || n == 0)
		return (dest);
	if (to > from && to - from < (int)n)
	{
		i = n;
		while (--i >= 0)
			to[i] = from[i];
		return (dest);
	}
	if (from > to && from - to < (int)n)
	{
		i = -1;
		while (++i < (int)n)
			to[i] = from[i];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}

/*
int main()
{
  char Src[] = "This is the content to be copied.";  

	char Dest[16] = {0};  
	ft_memmove(Dest, Src, 12);  
	printf("String after copying the n bytes: %s\n", Dest);  
	int dSrc[] = {20, 100, 30, 50, 70};  
	int n = sizeof(dSrc)/sizeof(dSrc[0]);  
	int dDestn[n], index = 0;  
	ft_memmove(dDestn, dSrc, sizeof(dSrc));  
	printf("\nNow after copying the array it is: ");  
	for (index=0; index<n; index++)  
	{  
		printf("%d ", dDestn[index]);  
	}  
	return 0;  
}
*/