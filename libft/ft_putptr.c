/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:20:31 by lblanche          #+#    #+#             */
/*   Updated: 2022/03/15 12:23:12 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	unsigned long	p;
	unsigned long	tmp;
	char			nbr[100];
	int				i;
	int				value;

	if (!ptr)
		return (ft_putstr("0x0"));
	i = 1;
	p = (unsigned long)ptr;
	ft_putstr("0x");
	while (p)
	{
		tmp = p % 16;
		if (tmp < 10)
			nbr[i] = tmp + 48;
		else
			nbr[i] = tmp + 87;
		p = p / 16;
		i++;
	}
	value = i;
	while (i - 1)
		ft_putchar(nbr[i-- - 1]);
	return (value + 1);
}
