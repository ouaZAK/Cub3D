/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 07:31:06 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/11 09:23:15 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


// void draw_player(t_cub3D *cb)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	j = -1;
// 	while(++i < COF_PIXEL)
// 	{
// 		j= 0;
// 		while(++j < COF_PIXEL)
// 		{
// 			if((i - j)*(i - j) < COF_PIXEL/2)
// 				mlx_put_pixel(cb->img, cb->player.x*COF_PIXEL + i, cb->player.y*COF_PIXEL + j,cb->p_color);
// 		}
// 	}
// 	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
// }


void	rays(void *v)
{
	t_cub3D	*cb;

	cb = v;
	float	next_x;
	float	next_y;
	float	mini_angl;
	float 	dis_x;
	float 	dis_y;
	float 	start = cb->angle - (AGNGLE_VUE / 2.0);
	float	ang_rays = AGNGLE_VUE / WINDOW_WIDTH;
	float	ray_dis;
	float	cast_hight;
	float	decalage;
	float	y_start_drawing;
	int i = -1;
	while (++i < WINDOW_WIDTH)
	{
		mini_angl = start + (ang_rays * i);
		dis_x = cos(mini_angl);
		dis_y = sin(mini_angl);
		next_x = cb->player.x;
		next_y = cb->player.y;
		while (cb->map.map_tmp[(int)next_y / COF_PIXEL][(int)next_x / COF_PIXEL] != '1')
		{
			next_x += dis_x;
			next_y += dis_y;
		}
		ray_dis = sqrt((next_x - cb->player.x) * (next_x - cb->player.x)
			+ (next_y - cb->player.y) * (next_y - cb->player.y));
		cast_hight = (COF_PIXEL * WINDOW_HEIGHT) / ray_dis;
		y_start_drawing = WINDOW_HEIGHT / 2 - (cast_hight / 2);
		decalage = cast_hight + (WINDOW_HEIGHT / 2 - (cast_hight / 2));
		while (++y_start_drawing < decalage)
		{
			if (y_start_drawing < WINDOW_HEIGHT)
				mlx_put_pixel(cb->img, i, y_start_drawing, 0x0000FFFF);
		}
	}
}

void    testing(t_cub3D *cb)
{
	// printf("height = %d\n", cb->map.height);
	// printf("width = %d\n", cb->map.width);
	cb->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT , "cub3D", false);
	cb->img = mlx_new_image(cb->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cb->img)
		handl_errors(2);
	mlx_image_to_window(cb->mlx, cb->img, 0, 0);
// Convert texture to a displayable image
	// mlx_image_t* img = mlx_texture_to_image(cb->mlx, cb->text[1].texture);
	// if (!img)
    //     handl_errors(1);
	mlx_loop_hook(cb->mlx, test, cb);
	mlx_loop_hook(cb->mlx, ft_hook, cb);
	// mlx_loop_hook(cb->mlx, rays, cb);
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
	// ft_free_float(cb.map.map_tmp);
	// system("leaks cub3D");
	return 0;
}