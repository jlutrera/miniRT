/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:13 by jutrera-          #+#    #+#             */
/*   Updated: 2023/01/07 23:05:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	process_flags2(char *s, va_list ap)
{
	t_flags	flags;

	flags = read_flags(s, ap);
	if (flags.type == 'c')
		return (ft_putchar_bonus((char)(va_arg(ap, int)), flags));
	else if (flags.type == '%')
		return (ft_putchar_bonus('%', flags));
	else if (flags.type == 's')
		return (ft_putstr_bonus(va_arg(ap, char *), flags));
	else if (flags.type == 'i' || flags.type == 'd')
		return (ft_putdigit(va_arg(ap, int), flags));
	else if (flags.type == 'u')
		return (ft_putunsigned(va_arg(ap, unsigned int), flags));
	else if (flags.type == 'x' || flags.type == 'X')
		return (ft_puthex(va_arg(ap, long), flags));
	else if (flags.type == 'p')
		return (ft_putpointer(va_arg(ap, void *), flags));
	else
		return (-1);
}

int	process_flags(char const *f, int *i, va_list ap)
{
	int		n;
	char	*s;
	int		j;

	n = *i;
	while (char_in_str(f[*i], "cspdiuxX%") == -1)
		++(*i);
	s = (char *)malloc(sizeof(char) * (*i - n + 2));
	if (!s)
		return (-1);
	j = 0;
	while (n < *i)
		s[j++] = f[n++];
	s[j++] = f[n];
	s[j] = '\0';
	n = process_flags2(s, ap);
	free(s);
	return (n);
}

int	ft_printf(char const *format, ...)
{
	va_list		ap;
	int			len;
	int			i;
	int			j;

	if (!format)
		return (-1);
	va_start(ap, format);
	len = 0;
	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			j = process_flags(format, &i, ap);
			if (j == -1)
				return (-1);
			len += j;
		}
		else
			len += ft_putchar(format[i]);
	}
	va_end(ap);
	return (len);
}
