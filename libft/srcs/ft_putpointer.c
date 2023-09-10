/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:32:18 by jutrera-          #+#    #+#             */
/*   Updated: 2022/10/03 23:32:18 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	puthex2(char *s, t_flags flags, int len)
{
	if (*s == '0' && flags.width <= 0 && flags.prec <= 0)
	{
		*s = '\0';
		len = 0;
	}
	if (flags.add)
		return (putdigit(s, flags, '+', len));
	else if (flags.space)
		return (putdigit(s, flags, ' ', len));
	else
		return (putdigit(s, flags, '0', len));
}

int	ft_putpointer(void *pointer, t_flags flags)
{
	int				i;
	int				len;
	char			*s;
	unsigned long	p;
	const char		g_base[] = "0123456789abcdef";

	if (!pointer)
		return (ft_putstr_bonus("0x0", flags));
	p = (unsigned long)pointer;
	len = ulen_number(p, 16);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (-1);
	s[len] = '\0';
	i = len;
	while (--i >= 0)
	{
		s[i] = g_base[p % 16];
		p /= 16;
	}
	return (putdigit(s, flags, '0', len));
}
