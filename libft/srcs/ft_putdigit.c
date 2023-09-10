/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:39:21 by jutrera-          #+#    #+#             */
/*   Updated: 2022/10/04 17:39:21 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putdigit(long n, t_flags flags)
{
	char	*s;
	int		len;
	char	c;

	c = 0;
	if (n < 0)
	{
		n *= -1;
		c = '-';
	}
	else if (flags.add)
		c = '+';
	else if (flags.space)
		c = ' ';
	s = ft_itoa(n);
	if (!s)
		return (-1);
	if (*s == '0' && flags.prec == 0)
		*s = '\0';
	len = len_str(s);
	return (putdigit(s, flags, c, len));
}
