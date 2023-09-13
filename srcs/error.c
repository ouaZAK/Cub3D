/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:57:08 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/31 10:42:48 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs.h"

void	handl_errors(int i)
{
	ft_printf("\033[1;31m");
	ft_printf("Error!\n");
	if (i == 1)
		ft_printf("Failed >> map unvalied \n");
	else if (i == 3)
		ft_printf("Failed >> border unvalid\n");
	else if (i == 4)
		ft_printf("Failed >> Upper / Lower boarder is not valid\n");
	else if (i == 5)
		ft_printf("Failed >> side boarder not valid\n");
	else if (i == 6)
		ft_printf("Failed >> reading error\n");
	else if (i == 7)
		ft_printf("Failed >> Moved outside map boarder\n");
	else if (i == 8)
		ft_printf("Failed >> No Valid Path \n");
	else if (i == 9)
		ft_printf("Failed >> 1 or More of Required Element Missing  \n");
	else if (i == 10)
		ft_printf("Failed >> No Valid Arguements! \n");
	ft_printf("\033[0m");
	exit(i);//! need to check if exit is alloweded
}
