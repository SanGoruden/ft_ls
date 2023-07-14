/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:23:48 by lblanche          #+#    #+#             */
/*   Updated: 2022/03/15 12:24:39 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hexl(unsigned int nbr)
{
	unsigned int	tmp;
	char			nbr_hex[100];
	int				i;
	int				value;

	i = 1;
	if (!nbr)
		return (ft_putchar('0'));
	while (nbr)
	{
		tmp = nbr % 16;
		if (tmp < 10)
			nbr_hex[i] = tmp + 48;
		else
			nbr_hex[i] = tmp + 87;
		nbr = nbr / 16;
		i++;
	}
	value = i - 1;
	while (i - 1)
		ft_putchar(nbr_hex[i-- - 1]);
	return (value);
}
