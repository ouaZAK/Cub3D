/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:55:13 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/13 11:03:23 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s || start >= ft_strlen(s))
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
