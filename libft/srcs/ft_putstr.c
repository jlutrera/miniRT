/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:31:36 by jutrera-          #+#    #+#             */
/*   Updated: 2022/10/03 23:31:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putstr(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		ft_putchar(s[i++]);
	return (i);
}

int	putstr_2(char *s, t_flags flags)
{
	char	fill;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fill = ' ';
	if (flags.zero)
		fill = '0';
	while (i++ < (flags.width - flags.prec))
		ft_putchar(fill);
	while (j < flags.prec && s[j] != '\0')
		ft_putchar(s[j++]);
	return (i + j - 1);
}

int	putstr_1(char *s, t_flags flags)
{
	int	i;

	i = 0;
	while (i < flags.prec && s[i] != '\0')
		ft_putchar(s[i++]);
	while (i++ < flags.width)
		ft_putchar(' ');
	return (i - 1);
}

int	ft_putstr_bonus(char *s, t_flags flags)
{
	int		n;

	if (!s)
		return (ft_putstr_bonus("(null)", flags));
	n = len_str(s);
	if (flags.prec == -1 || flags.prec > n)
		flags.prec = n;
	if (flags.prec < n || flags.width > n)
	{
		if (flags.minus)
			return (putstr_1(s, flags));
		else
			return (putstr_2(s, flags));
	}
	return (ft_putstr(s));
}
