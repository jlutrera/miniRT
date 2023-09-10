/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:42:11 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/18 14:27:46 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int arg)
{
	if ((arg >= 'A' && arg <= 'Z')
		|| (arg >= 'a' && arg <= 'z'))
		return (arg);
	return (0);
}
/*
#include <stdio.h>
int  main(void)
{
	unsigned char c;

	printf("Enter a character: ");
	scanf("%c", &c);
	if (ft_isalpha(c) == 0)
		 printf("%c is not an alphabet.", c);
	else
		 printf("%c is an alphabet.", c);

	return 0;
}
*/