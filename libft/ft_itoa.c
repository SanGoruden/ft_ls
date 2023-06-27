/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:49:28 by lblanche          #+#    #+#             */
/*   Updated: 2022/02/24 12:53:10 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	else
		len = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static int	is_negative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	get_nbr(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				negative;
	int				len;
	char			*str;

	negative = is_negative(n);
	str = NULL;
	len = ft_len(n);
	nbr = get_nbr(n);
	str = malloc(sizeof(char) * len +1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	if (negative == 1)
		str[0] = '-';
	return (str);
}

/*
#include <stdio.h>

int		main(void)
{
	printf("\n%s\n", ft_itoa(10050003));
}
*/
