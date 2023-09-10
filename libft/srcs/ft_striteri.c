/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:11:30 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/25 12:41:16 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (f && s)
	{
		while (s[i] != 0)
		{
			f(i, s + i);
			i++;
		}
	}
}
/*
#include <stdio.h>
void f(unsigned int i, char *s)
{
	*s = *s + 32;
}

int main()
{
	char str[] = "ABCDEF";

	ft_striteri(str, f);
	printf("%s\n", str);
}
*/