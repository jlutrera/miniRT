/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:11:43 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/27 18:34:37 by jutrera-         ###   ########.fr       */
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
/*
int main () {
   int i, n;
   int *a;

   printf("Number of elements to be entered:");
   scanf("%d",&n);

   a = (int*)ft_calloc(n, sizeof(int));
   printf("Enter %d numbers:\n",n);
   for( i=0 ; i < n ; i++ ) {
	  scanf("%d",&a[i]);
   }

   printf("The numbers entered are: ");
   for( i=0 ; i < n ; i++ ) {
	  printf("%d ",a[i]);
   }
   free( a );
   
   return(0);
}
*/