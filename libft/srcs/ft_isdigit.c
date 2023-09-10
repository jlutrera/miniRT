/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:42:11 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/18 14:28:52 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (arg);
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
		 printf("%c is not a digit.", c);
	else
		 printf("%c is a digit.", c);

	return 0;
}
*/