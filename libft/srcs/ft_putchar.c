/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:38:33 by jutrera-          #+#    #+#             */
/*   Updated: 2022/10/03 23:38:33 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putchar_bonus(char c, t_flags flags)
{
	int		i;
	char	fill;

	if (flags.width > 0)
	{
		i = 1;
		fill = ' ';
		if (flags.minus)
		{
			ft_putchar(c);
			while (i++ < flags.width)
				ft_putchar(fill);
		}
		else
		{
			if (flags.zero)
				fill = '0';
			while (i++ < flags.width)
				ft_putchar(fill);
			ft_putchar(c);
		}
		return (flags.width);
	}
	else
		return (ft_putchar(c));
}
