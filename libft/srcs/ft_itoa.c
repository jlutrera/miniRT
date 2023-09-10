/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:04:10 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/25 13:41:23 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	len_n(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*nb;
	int				len;
	unsigned int	num;

	len = len_n(n);
	nb = (char *)malloc((len + 1) * sizeof(char));
	if (!nb)
		return (0);
	if (n == 0)
		nb[0] = '0';
	if (n < 0)
	{
		nb[0] = '-';
		num = -n;
	}
	else
		num = n;
	nb[len] = '\0';
	while (num > 0)
	{
		nb[--len] = num % 10 + '0';
		num /= 10;
	}
	return (nb);
}
/*
#include <stdio.h>
int main()
{
	int n;

	n = 0;
	printf("El numero es el %s \n", ft_itoa(n));
}
*/