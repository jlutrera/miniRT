/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:41:06 by jutrera-          #+#    #+#             */
/*   Updated: 2022/10/03 23:41:06 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	puthex(char *s, t_flags flags, int len)
{
	if (*s == '0' && (flags.width == 0 || flags.prec == 0))
	{
		*s = '\0';
		return (putdigit(s, flags, 0, 0));
	}
	if (flags.sharp && *s != '0')
		return (putdigit(s, flags, '0', len));
	else if (flags.add)
		return (putdigit(s, flags, '+', len));
	else if (flags.space)
		return (putdigit(s, flags, ' ', len));
	else
		return (putdigit(s, flags, 0, len));
}

int	ft_puthex(unsigned int nb, t_flags flags)
{
	int			i;
	int			len;
	char		*s;
	const char	g_base[] = "0123456789abcdef";

	len = len_number(nb, 16);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (-1);
	s[len] = '\0';
	i = len;
	while (--i >= 0)
	{
		s[i] = g_base[nb % 16];
		if ((s[i] > '9') && (flags.type == 'X'))
			s[i] -= 32;
		nb /= 16;
	}
	return (puthex(s, flags, len));
}
