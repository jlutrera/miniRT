/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:15:40 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/29 21:15:40 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == 45 || str[i] == 43))
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *strings[5] = {
		"  +123",
		"0.33",
		"7lucky",
		"string",
		"-2147483648"
	};

	puts("  String\tAs int");
	for(int x=0;x<5;x++)
	{
		printf("%d: %-7s\t%d\n",
				x+1,
				strings[x],
				ft_atoi(strings[x]));
	}

	return(0);
}
*/