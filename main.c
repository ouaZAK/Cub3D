/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/13 14:43:50 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    testing(t_cub3D *cb)
{
	// printf("height = %d\n", cb->map.height);
	// printf("width = %d\n", cb->map.width);
	cb->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT , "cub3D", false);
	cb->img = mlx_new_image(cb->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cb->img2 = mlx_new_image(cb->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
	mlx_image_to_window(cb->mlx, cb->img2, 0, 0);
	// map(cb);
	
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	mlx_loop_hook(cb->mlx, test, cb);
	// mlx_loop_hook(cb->mlx, walls, cb);
	// mlx_loop_hook(cb->mlx, map, cb);
	mlx_loop(cb->mlx);
}

int main(int ac, char **av)
{
	t_cub3D cb;

	if (ac != 2)
		handl_errors(10);
	init_cub3D(&cb);
	cb.fd = open(av[1], O_RDONLY);
	if (cb.fd == -1 || check_parameters(av[1]) == 0 || check_content(&cb))
		handl_errors(6);
	testing(&cb);
//copy maptmp to stack map but its not good 
	// int a;
	// int b;
	// int x;
	// int y;
	// int tmp;
	// int tmp2;
	
	// y = 0;
	// a = 0;
	// tmp = COF_PIXEL;
	// tmp2 = 5;//nbr row
	// while (cb.map.map_tmp[y])
	// {
	// 	while (a < tmp2)
	// 	{
	// 		x = 0;
	// 		b = 0;
	// 		tmp = COF_PIXEL;
	// 		while (cb.map.map_tmp[y][x])
	// 		{
	// 			while (b < tmp)
	// 				cb.map.map[a][b++] = cb.map.map_tmp[y][x];
	// 			x++;
	// 			tmp += COF_PIXEL;
	// 		}
	// 		cb.map.map[a][b] = '\0';
	// 		a++;
	// 	}
	// 	tmp2 += 5;
	// 	y++;
	// }
	// *cb.map.map[a] = '\0';
	// ft_free_double(cb.map.map_tmp);
	// system("leaks -q cub3D");
	return 0;
}