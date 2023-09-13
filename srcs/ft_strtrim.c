/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:56:35 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/13 14:47:16 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs.h"

int	check(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*sub;
	int		s1len;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	s1len = ft_strlen(s1) - 1;
	while (s1[i] && check(s1[i], set))
		i++;
	while (s1[s1len] && s1len > i && check(s1[s1len], set))
		s1len--;
	sub = ft_substr(s1, i, (s1len - i + 1));
	// printf("sub [%p]  <%s>\n",sub, sub);
	// free(s1);
	return (sub);
}
