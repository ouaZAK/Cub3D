/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_move.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:48 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/11 16:21:57 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
//! i didn't uset because it print ligne but i can't move it around 
// void draw_line(mlx_image_t *img, int start_x, int start_y, int end_x, int end_y, size_t color)
// {
//     int x0 = start_x;
//     int y0 = start_y;
//     int x1 = end_x;
//     int y1 = end_y;
//     int x = x0;
//     int y = y0;

//     int dx1 = abs(x1 - x0);
//     int dy1 = abs(y1 - y0);
//     int sx = x0 < x1 ? 1 : -1;
//     int sy = y0 < y1 ? 1 : -1;
//     int err = dx1 - dy1;

//     while (x != x1 || y != y1)
//     {
//         // if(x >=0 && x < max.x && y>= 0 && y < max.y)
//         // printf("x: %d   y: %d\n",x,y);
//         mlx_put_pixel(img, x, y, color);
//         int e2 = 2 * err;
//         if (e2 > -dy1)
//         {
//             err -= dy1;
//             x += sx;
//         }
//         if (e2 < dx1)
//         {
//             err += dx1;
//             y += sy;
//         }
//     }
// }
void    draw_line(mlx_image_t *image, int startx, int starty, int endx, int endy, int color)
{
    int    delta_x = endx - startx;
    int    delta_y = endy - starty;
    int step_x = 1;
    int step_y = 1;
    if (delta_x < 0)
    {
        delta_x = -delta_x;
        step_x = -1;
    }
    if (delta_y < 0)
    {
        delta_y = -delta_y;
        step_y = -1;
    }
    delta_y*=-1;
    int error;
    int error2 = 0;
    error = delta_y+delta_x;
    while (1)
    {
        if (startx >= 0 && startx < WINDOW_WIDTH && starty >= 0 && starty < WINDOW_HEIGHT)
            mlx_put_pixel(image, startx, starty, color);
        if (startx == endx && starty == endy)
            break;
        error2 = error*2;
        if (error2 >= delta_y)
        {
            if (startx == endx)
                break;
            error+=delta_y;
            startx+=step_x;
        }
        if (error2 <= delta_x)
        {
            if (starty == endy)
                break;
            error+=delta_x;
            starty+=step_y;
        }
    }
}

// int check_wall(t_cub3D *cb)
// {
// 	if (cb->map.map_tmp[(int)((cb->player.y + COF_PIXEL/2)/COF_PIXEL)][(int)((cb->player.x + COF_PIXEL/2)/COF_PIXEL)] == '1')
// 		return (0);
// 	// 	return (1);
// 	return (1);
// }

int is_wall_pixel(t_cub3D *cb, float x, float y)
{
	int pos_y;
	int pos_x;

	if (y / COF_PIXEL  < 1 || x / COF_PIXEL < 1
		|| y / COF_PIXEL > cb->map.height - 1 || x / COF_PIXEL  > cb->map.width - 1)
		return (0);
	
	pos_y = y / COF_PIXEL;
	pos_x = x / COF_PIXEL;
	// // printf("x[%f] y=[%f] xp[%d] yp=[%d] hi [%d] wid [%d]\n",x, y,pos_x,pos_y, cb->map.height, cb->map.width);// it segfault when it goes down
	if (pos_x < 0 || pos_y < 0 || pos_x > cb->map.width || pos_y > cb->map.height)
	{
		printf("we out of maps and x is %d and y is %d\n", pos_x, pos_y);		
		return (0);
	}
	// printf("the wall check is check[%d][%d]\n",pos_y, pos_x);
	if (cb->map.map_tmp[pos_y][pos_x] == '1')
		return (0);
	return (1);

}

/* appreciate the effor */
// void	draw_ray(t_cub3D *cb)
// {
// 	float x_ray = cb->player.x;
// 	float y_ray = cb->player.y;
// 	float next_x = cb->player.10;
// 	float next_y = cb->player.10;
// 	while (is_wall_pixel(cb, next_x, y_ray) && is_wall_pixel(cb, x_ray, next_y))
// 	{
// 		next_x = x_ray + cos(cb->angle * M_PI / 180) * COF_PIXEL / 2;
// 		next_y = y_ray + sin(cb->angle * M_PI / 180) * COF_PIXEL / 2;
// 		x_ray = next_x;
// 		y_ray = next_y;
// 	}
// 	cb->ray_dis = sqrt((cb->player.x - x_ray) * (cb->player.x - x_ray)
// 		+ (cb->player.y - y_ray) * (cb->player.y - y_ray));
// 	// printf ("[%f]\n", ray_dis);
// }

//! this function is used to change player angle
void change_angle(t_cub3D *cb, int KEY)
{
	if (KEY == MLX_KEY_RIGHT)
	{
		cb->angle += 0.01;
		if (cb->angle >= 2 * M_PI)
			cb->angle -= 2 * M_PI;
	}
	else if (KEY == MLX_KEY_LEFT)
	{
		cb->angle -= 0.01;
		if (cb->angle < 0)
			cb->angle += 2 * M_PI;
	}
	// if (KEY == MLX_KEY_RIGHT && (cb->angle) <= 360 - 1)
	// 	cb->angle = (cb->angle + 1) % 360;
	// else if (KEY ==  MLX_KEY_LEFT && cb->angle >= 1)
	// 	cb->angle = (cb->angle - 1) % 360;
	// else if (cb->angle == 0 && KEY == MLX_KEY_LEFT)
	// 	cb->angle = 360 - 1;
}

//! this function to change player position
void change_player(t_cub3D *cb, int KEY)
{
	int next_x;
	int next_y;
	if (KEY == MLX_KEY_W)
	{
		next_x = cb->player.x + (cos(cb->angle) * 4);
		next_y = cb->player.y + (sin(cb->angle) * 4);
		if(cb->map.map_tmp[(int)next_y / COF_PIXEL][(int)cb->player.x/COF_PIXEL] != '1')
			cb->player.y = next_y;
		if(cb->map.map_tmp[(int)cb->player.y/COF_PIXEL][(int )next_x / COF_PIXEL] != '1')
			cb->player.x = next_x;
	}
	
	if (KEY == MLX_KEY_S)
	{
		next_x = cb->player.x + (cos(cb->angle + M_PI) * 4);
		next_y = cb->player.y + (sin(cb->angle + M_PI) * 4);
		if(cb->map.map_tmp[(int )next_y / COF_PIXEL][(int)cb->player.x/COF_PIXEL] != '1')
			cb->player.y = next_y;
		if(cb->map.map_tmp[(int)cb->player.y/COF_PIXEL][(int )next_x / COF_PIXEL] != '1')
			cb->player.x = next_x;
	}
	if (KEY == MLX_KEY_A)
	{
		next_x = cb->player.x + (cos(cb->angle - ( M_PI / 2)) * 4);
		next_y = cb->player.y + (sin(cb->angle - ( M_PI / 2)) * 4);
		if(cb->map.map_tmp[(int )next_y / COF_PIXEL][(int)cb->player.x/COF_PIXEL] != '1')
			cb->player.y = next_y;
		if(cb->map.map_tmp[(int)cb->player.y/COF_PIXEL][(int )next_x / COF_PIXEL] != '1')
			cb->player.x = next_x;
	}
	if (KEY == MLX_KEY_D)
	{
		next_x = cb->player.x + (cos(cb->angle +( M_PI / 2)) * 4);
		next_y = cb->player.y + (sin(cb->angle +( M_PI / 2)) * 4);
		if(cb->map.map_tmp[(int )next_y / COF_PIXEL][(int)cb->player.x/COF_PIXEL] != '1')
			cb->player.y = next_y;
		if(cb->map.map_tmp[(int)cb->player.y/COF_PIXEL][(int )next_x / COF_PIXEL] != '1')
			cb->player.x = next_x;
	}
}

float angle_overlap(float angle)
{
	if (angle < 0)
		angle+=2*M_PI;
	else if (angle > 2*M_PI)
		angle-=2*M_PI;
	return (angle);
}

void	test(void *param)
{
	t_cub3D  *cb = param;
	float hx;
	float hy;
	float vx;
	float vy;
	float ra;
	float hyblock;
	float hxblock;
	float vxblock;
	float vyblock;
	float angle_step;
	float atan;
	int rx,ry;
	float dis_w;
	int x = cb->player.x;
	int y = cb->player.y;
	int i = -1;

	draw_C_F(cb);
	draw_map(cb);
	ra = cb->angle - (AGNGLE_VUE / 2 * (M_PI / 180));
	angle_step = (AGNGLE_VUE * (M_PI / 180) / WINDOW_WIDTH);
	while (++i < WINDOW_WIDTH)
	{
		ra = angle_overlap(ra);
		atan = -1 / tan(ra);
		if (ra > M_PI)
		{
			hy = ((y / COF_PIXEL) * COF_PIXEL) - 0.0001;
			hx = x + (y - hy) * atan;
			hyblock = -COF_PIXEL;
			hxblock = -hyblock * atan;
		}
		else if (ra < M_PI)
		{
			hy = ((y / COF_PIXEL) * COF_PIXEL) + COF_PIXEL;
			hx = x + (y - hy) * atan;
			hyblock = COF_PIXEL;
			hxblock = -hyblock * atan;
		}
		if (ra == 0 || ra == M_PI)
		{
			hx = x;
			hy = y;
		}
		while (hy < WINDOW_HEIGHT && hy > 0)
		{
			if (hx > WINDOW_WIDTH || hx < 0)
				break ;
			else if (!is_wall_pixel(cb, hx, hy))
				break ;
			hx += hxblock;
			hy += hyblock;
		}
		
		atan = -tan(ra);
		if (ra > (3 * M_PI) / 2 || ra < M_PI / 2)
		{
			vx = ((x / COF_PIXEL) * COF_PIXEL) + COF_PIXEL;
			vy = y + (x - vx) * atan;
			vxblock = COF_PIXEL;
			vyblock = -vxblock * atan;
		}
		else if (ra < (3 * M_PI) / 2 && ra > M_PI / 2)
		{
			vx = ((x / COF_PIXEL) * COF_PIXEL) - 0.0001;
			vy = y + (x - vx) * atan;
			vxblock = -COF_PIXEL;
			vyblock = -vxblock * atan;
		}
		if (ra == 0 || ra == M_PI)
		{
			hx = x;
			hy = y;
		}

		while (vx < WINDOW_WIDTH && vx > 0)
		{
			if (vy > WINDOW_HEIGHT || vy < 0)
				break ;
			else if (!is_wall_pixel(cb, vx, vy))
				break ;
			vx += vxblock;
			vy += vyblock;
		}
		
		float dis_h = sqrtf(((hx - x) * (hx - x)) + ((hy - y) * (hy - y)));
		float dis_v = sqrtf(((vx - x) * (vx - x)) + ((vy - y) * (vy - y)));
		if (dis_h < dis_v)
		{
			dis_w = dis_h;
			rx = hx;
			ry = hy;
		}
		else
		{
			dis_w = dis_v;
			rx = vx;
			ry = vy;
		}
		dis_w = cos(((AGNGLE_VUE / 2) * M_PI / 180) - (i * angle_step)) * dis_w;
		// float angle = ra - cb->angle;//ayman
		// angle =  angle_overlap(angle);
		// float final_dist = cos(angle) * dis_w;
		
		float Projection_to_wall = ((float)WINDOW_HEIGHT/4)/-tan(30) * ((float)WINDOW_HEIGHT/dis_w);
		Projection_to_wall *= 2;
		// int Projection_to_wall = WINDOW_HEIGHT / final_dist * 50;//ayman
		if (Projection_to_wall > WINDOW_HEIGHT)
			Projection_to_wall = WINDOW_HEIGHT;
		draw_line(cb->img, x/4, y/4, rx/4, ry/4, 0x000000FF);//line draw
		int y_wall = WINDOW_HEIGHT/2-(Projection_to_wall/2);
		// draw_line(cb->img, i, y_wall, i, y_wall + Projection_to_wall, 0x0000ddFF);//line draw
		while (y_wall < WINDOW_HEIGHT/2+(Projection_to_wall/2))
		{
			mlx_put_pixel(cb->img, i, y_wall, 0x0000ffff);
			y_wall++;
		}
		ra += angle_step;
	}
}

//! this function for key hook so every key do action functionality
void ft_hook(void* param)
{
	t_cub3D  *cb = param;

	if (mlx_is_key_down(cb->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cb->mlx);
	if(mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		change_angle(cb, MLX_KEY_LEFT);
	if(mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		change_angle(cb, MLX_KEY_RIGHT);
	if(mlx_is_key_down(cb->mlx, MLX_KEY_W))
		change_player(cb, MLX_KEY_W);
	if(mlx_is_key_down(cb->mlx, MLX_KEY_S))
		change_player(cb, MLX_KEY_S);
	if(mlx_is_key_down(cb->mlx, MLX_KEY_A))
		change_player(cb, MLX_KEY_A);
	if(mlx_is_key_down(cb->mlx, MLX_KEY_D))
		change_player(cb, MLX_KEY_D);
	// else if(mlx_is_key_down(cb->mlx, MLX_KEY_UP))
	// 	{

	// 		mlx_draw_line(cb, 0, 0, 100, 100, 0xFF0000FF);			
	// 		// printf("up\n");
	// 	}
	// mlx_close_window(mlx);
	// draw_ray(cb);//appreciate the effort
	
	// test(cb);
	// draw_player(cb, cb->angle, cb->ray_dis, 1);//appreciate the effort
	// draw_player(cb, cb->angle, COF_PIXEL / 2, AGNGLE_VUE);
}
