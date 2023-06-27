/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:40:11 by lblanche          #+#    #+#             */
/*   Updated: 2022/02/28 14:38:37 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_long(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	if (i > 10)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	negative;

	n = 0;
	negative = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		negative = 1;
		nptr++;
	}
	if (*nptr == '+' && !negative)
		nptr++;
	if (is_long(nptr) && !negative)
		return (-1);
	else if (is_long(nptr) && negative)
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
		n = n * 10 + *nptr++ - '0';
	if (negative)
		n *= -1;
	return (n);
}

/*
#include <stdio.h>

int		main(int argc, char **argv)
{
	(void)argc;
	printf("%d\n", ft_atoi(argv[1]));
}
*/
