/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:38:15 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/11 19:18:50 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	if_player(char c)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

//draw ceiling and floor
void	draw_C_F(t_cub3D *cb)
{
	uint32_t	color_C;
	uint32_t	color_F;
	int			x;
	int			y;

	y = -1;
	color_C = ft_pixel(cb->colors[C].r, cb->colors[C].g, cb->colors[C].b, 255);
	color_F = ft_pixel(cb->colors[F].r, cb->colors[F].g, cb->colors[F].b, 255);
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				mlx_put_pixel(cb->img, x, y, color_C);
			else if (y >= WINDOW_HEIGHT / 2)
				mlx_put_pixel(cb->img, x, y, color_F);
		}
	}
}

void draw_map(t_cub3D *cb)
{
	int				x;
	int				y;
	int				i;
	int				j;

	y = -1;
	while (cb->map.map_tmp[++y])
	{
		x = -1;
		while (cb->map.map_tmp[y][++x])
		{
			j = -1;
			while (++j < (COF_PIXEL/4) - 1)
			{
				i = -1;
				while (++i < (COF_PIXEL/4) - 1)
				{
					if (cb->map.map_tmp[y][x] == '1') 
						mlx_put_pixel(cb->img2, (x  * COF_PIXEL)/4 + i, (y * COF_PIXEL)/4 + j, 0x00FFFFFF);
					else if (cb->map.map_tmp[y][x] == '0' || if_player(cb->map.map_tmp[y][x]))
						mlx_put_pixel(cb->img2, (x  * COF_PIXEL)/4 + i, (y * COF_PIXEL)/4 + j, 0xFFFFFFFF);
				}
			}
		}
	}
}

// void draw_player(t_cub3D *cb, int playerSize, int angle_vue)
// {
//     int i;
//     int j;
// 	int x;
// 	int y;
//     int centerX = cb->player.x;
//     int centerY = cb->player.y;
// 	// angle += 90; //for ajustement
//     i = -playerSize;
//     while (++i <= playerSize)
//     {
//         j = -playerSize;
//         while (++j <= playerSize)
//         {
//             x = centerX + i;
//             y = centerY + j;

//             // Calculate distance from center of the player symbol
//             int distance = sqrt(i * i + j * j);

//             // Calculate angle between the point and player's direction
//             float pointAngle = atan2(y - centerY, x - centerX) * 180.0 / PI;
//             int angleDifference = abs(angle - (int)pointAngle);
//             angleDifference = fmin(angleDifference, 360 - angleDifference) ;

//             // Check if the point is within the desired shape
//             if (distance <= playerSize && angleDifference <= angle_vue && is_wall_pixel(cb, (float)x,(float)(y),cb->angle))
//             {
// 				mlx_put_pixel(cb->img, x, y, 0xFF0000FF);
//             }
//         }
//     }
// }

void draw_player(t_cub3D *cb, int playerSize, int angle_vue) {
    int centerX = (int)cb->player.x;
    int centerY = (int)cb->player.y;
    int radius = playerSize;

    int angle = 0;
    while (angle < 360) {
        double radians = (angle + angle_vue) * (PI / 180.0);
        int x = centerX + (int)(radius * cos(radians));
        int y = centerY + (int)(radius * sin(radians));

        // Draw or render the circle point at (x, y) here
		mlx_put_pixel(cb->img, x, y, 0xFF0000FF);
        angle++;
    }
	// printf("im here\n");

    // Draw a small arrow to indicate the player's direction
    double directionRadians = (angle_vue) * (PI / 180.0);
    int arrowX = centerX + (int)((radius + 10) * cos(directionRadians));
    int arrowY = centerY + (int)((radius + 10) * sin(directionRadians));
	// mlx_draw_line(cb, centerX, centerY, arrowX, arrowY, 0xFF0000FF);

    // Draw or render the arrow at (arrowX, arrowY) here
}