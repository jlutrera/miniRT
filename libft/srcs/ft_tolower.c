/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:12:38 by jutrera-          #+#    #+#             */
/*   Updated: 2022/09/18 14:30:41 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
			c += 32;
	return (c);
}
/*
#include <stdio.h>
int main() {
    char c;

    c = 'm';
    printf("%c -> %c", c, ft_tolower(c));

    c = 'D';
    printf("\n%c -> %c", c, ft_tolower(c));

    c = '9';
    printf("\n%c -> %c", c, ft_tolower(c));
    return 0;
}
*/