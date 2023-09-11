/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:28:35 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/20 08:39:32 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs.h"

static int	ft_size_malloc(const char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] != c)
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			len++;
		}
		while (str[i] == c && str[i] != '\0')
			i++;
	}
	return (len + 1);
}

static char	*ft_add_mot(const char *str, int i, int j)
{
	int		len_mot;
	int		k;
	char	*mot;

	mot = 0;
	len_mot = (j - i + 1) + 1;
	mot = (char *)malloc (len_mot * sizeof(char));
	if (!mot)
		return (0);
	k = 0;
	while (k < len_mot - 1)
	{
		mot[k] = str[i + k];
		k++;
	}
	mot[k] = '\0';
	return (mot);
}

static void	ft_init(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

char	**ft_split(const char *str, char c)
{
	char	**result;
	int		i;
	int		j;
	int		k;

	ft_init(&i, &j, &k);
	result = (char **)malloc (ft_size_malloc (str, c) * sizeof(char *));
	if (!result || !str)
		return (0);
	while (str && str[i] != '\0')
	{
		j = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if (i != j)
			result[k++] = ft_add_mot(str, j, i - 1);
		while (str[i] == c && str[i] != '\0')
			i++;
	}
	result[k] = 0;
	return (result);
}
