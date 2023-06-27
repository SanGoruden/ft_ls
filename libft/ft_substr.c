/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:44:27 by lblanche          #+#    #+#             */
/*   Updated: 2022/02/24 12:44:53 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	int		i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		s2 = malloc(sizeof(char) * 1);
		if (!s2)
			return (NULL);
		s2[0] = '\0';
		return (s2);
	}
	i = 0;
	s2 = malloc(((len + 1) * sizeof(char)));
	if (!s2)
		return (NULL);
	while (s[i + start] && len--)
	{
		s2[i] = s[i + start];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
