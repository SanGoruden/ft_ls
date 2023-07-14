/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:19:31 by lblanche          #+#    #+#             */
/*   Updated: 2022/03/15 12:20:07 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long long n)
{
	unsigned long long	nb;
	int					len;

	len = 0;
	if (n < 0)
	{
		ft_putchar('-');
		nb = -n;
		len = 1;
	}
	else
		nb = n;
	len += nbr_len(nb);
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		nb %= 10;
	}
	ft_putchar(nb + '0');
	return (len);
}
