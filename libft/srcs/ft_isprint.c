/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:27:58 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/18 14:30:04 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int arg)
{
	if (arg >= 32 && arg <= 126)
		return (arg);
	return (0);
}
/*
#include <stdio.h>
int main(void)
{
	int c;
	printf("The printable characters are: \n");
   	for (c = 1; c <= 127; ++c)
   		if (ft_isprint(c)!= 0)
             printf("%c ", c);
    return 0;
}
*/