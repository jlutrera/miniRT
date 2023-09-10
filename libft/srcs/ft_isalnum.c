/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:42:11 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/18 14:26:26 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int arg)
{
	if ((arg >= '0' && arg <= '9')
		|| (arg >= 'a' && arg <= 'z')
		|| (arg >= 'A' && arg <= 'Z'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
int  main(void)
{
	unsigned char c;

	printf("Enter a number: ");
	scanf("%c", &c);

	if (ft_isdigit(c) == 0)
		 printf("%c is not alphanumeric.", c);
	else
		 printf("%c is alphanumeric.", c);

	return 0;
}
*/