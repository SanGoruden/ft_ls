/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:24:30 by lblanche          #+#    #+#             */
/*   Updated: 2022/03/15 13:41:05 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	process_arg(const char *str, int i, va_list *ap, int value)
{
	if (str[i + 1] == 'c')
		value += ft_putchar(va_arg(*ap, int));
	else if (str[i + 1] == 's')
		value += ft_putstr(va_arg(*ap, char *));
	else if (str[i + 1] == 'p')
		value += ft_putptr(va_arg(*ap, void *));
	else if (str[i + 1] == 'i' || str[i + 1] == 'd')
		value += ft_putnbr(va_arg(*ap, int));
	else if (str[i + 1] == 'u')
		value += ft_putnbr_u(va_arg(*ap, unsigned int));
	else if (str[i + 1] == 'x')
		value += ft_putnbr_hexl(va_arg(*ap, unsigned int));
	else if (str[i + 1] == 'X')
		value += ft_putnbr_hexu(va_arg(*ap, unsigned int));
	else if (str[i + 1] == '%')
		value += ft_putchar('%');
	return (value);
}

static int	is_charset(char c)
{
	int		i;
	char	set[9];

	i = 0;
	set[0] = 'c';
	set[1] = 's';
	set[2] = 'p';
	set[3] = 'i';
	set[4] = 'u';
	set[5] = 'd';
	set[6] = 'x';
	set[7] = 'X';
	set[8] = '%';
	while (i < 10)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		value;

	i = 0;
	value = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] != '%')
			value += ft_putchar(str[i]);
		else
		{
			value = process_arg(str, i, &ap, value);
			if (is_charset(str[i + 1]))
				i++;
		}
		i++;
	}
	va_end(ap);
	return (value);
}
