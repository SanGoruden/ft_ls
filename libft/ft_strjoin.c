/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblanche <lblanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:42:45 by lblanche          #+#    #+#             */
/*   Updated: 2022/02/28 13:55:59 by lblanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_str;

	if (!s1 || !s2)
		return (NULL);
	len_str = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len_str * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(str, (char *)s2, len_str + 1);
	return (str);
}
