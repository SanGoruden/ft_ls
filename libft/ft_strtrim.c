/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:43:23 by lblanche          #+#    #+#             */
/*   Updated: 2022/02/24 12:44:23 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	get_str_size(char const *s1, char *str_start, char *str_end)
{
	size_t	str_size;

	if (!*s1 || str_end == str_start)
		str_size = 2;
	else
		str_size = str_end - str_start + 2;
	return (str_size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	str_size;
	char			*str_start;
	char			*str_end;
	char			*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	str_start = (char *)&s1[i];
	i = ft_strlen(s1) - 1;
	if (i != -1)
		while (i >= 0 && is_in_set(s1[i], set))
			i--;
	str_end = (char *)&s1[i];
	str_size = get_str_size(s1, str_start, str_end);
	str = malloc(sizeof(char) * str_size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, str_start, str_size);
	return (str);
}
