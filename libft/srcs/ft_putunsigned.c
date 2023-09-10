/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:48:56 by jutrera-          #+#    #+#             */
/*   Updated: 2022/10/04 17:48:56 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putunsigned(unsigned long n, t_flags flags)
{
	char	*s;
	int		len;
	char	c;

	c = 0;
	if (flags.add)
		c = '+';
	else if (flags.space)
		c = ' ';
	s = ft_uitoa(n);
	if (!s)
		return (-1);
	if (*s == '0' && flags.prec == 0)
		*s = '\0';
	len = len_str(s);
	return (putdigit(s, flags, c, len));
}
