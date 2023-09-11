/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 06:42:51 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/21 11:58:11 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs.h"

int	ft_atoi(const char *str)
{
	int							i;
	unsigned long long int		n;

	i = 0;
	n = 0;
	// if (str[0] == '0' && !str[1])
	// 	return (0);
	while (str[i] <= '9' && str[i] >= '0')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	if (str[i])
		return (-1);
	// if (n > MAX_INT || n < MIN_INT)
	// 		return (-1);
	return ((int)n);
}
