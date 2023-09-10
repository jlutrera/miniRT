/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:42:11 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/24 15:48:05 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int arg)
{
	if ((unsigned int)arg <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int  main(void)
{
	unsigned char c;

	printf("Enter a character: ");
	scanf("%c", &c);

	if (ft_isdigit(c) == 0)
		 printf("%c can not be represented by an ASCII character.", c);
	else
		 printf("The character is %c", c);

	return 0;
}
*/