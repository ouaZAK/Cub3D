/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_move.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:57:48 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/12 14:56:25 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

//! i didn't uset because it print ligne but i can't move it around 
void mlx_draw_line(t_cub3D *cb, int x1, int y1, int x2, int y2, uint32_t color)
{
	if (x2 < 0  || y2 < 0)
		return;
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;
	// printf("the player[%d][%d] and wall[%d][%d]\n", x1, y1, x2, y2);
	mlx_put_pixel(cb->img, x1, y1, color);
	while (x1 != x2 && y1 != y2)
	{
		mlx_put_pixel(cb->img, x1, y1, color);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void draw_line(mlx_image_t *img, int start_x, int start_y, int end_x, int end_y, size_t color)
{
    int x0 = start_x;
    int y0 = start_y;
    int x1 = end_x;
    int y1 = end_y;
    int x = x0;
    int y = y0;

    int dx1 = abs(x1 - x0);
    int dy1 = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx1 - dy1;

    while (x != x1 || y != y1)
    {
        // if(x >=0 && x < max.x && y>= 0 && y < max.y)
        // printf("x: %d   y: %d\n",x,y);
        mlx_put_pixel(img, x, y, color);
        int e2 = 2 * err;
        if (e2 > -dy1)
        {
            err -= dy1;
            x += sx;
        }
        if (e2 < dx1)
        {
            err += dx1;
            y += sy;
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
	// if (angle >= 0 && angle <= 90)
	// {
	// 	pos_y = (y + 1)/ COF_PIXEL;
	// 	pos_x = (x + 1) / COF_PIXEL;
	// }
	// else if (angle > 90 && angle <= 180)
	// {
	// 	pos_y = (y + 1) / COF_PIXEL;
	// 	pos_x = (x - 1) / COF_PIXEL;

	// }
	// else if (angle > 180 && angle <= 270)
	// {
	// 	pos_y = (y - 1) / COF_PIXEL;
	// 	pos_x = (x - 1) / COF_PIXEL;
	// }
	// else if (angle > 270 && angle < 360)
	// {
	// 	pos_y = (y - 1) / COF_PIXEL;
	// 	pos_x = (x + 1) / COF_PIXEL;
		
	// }
	if (cb->map.map_tmp[pos_y][pos_x] == '1')
		return (0);
	return (1);

}

/* appreciate the effor */
// void	draw_ray(t_cub3D *cb)
// {
// 	float x_ray = cb->player.x;
// 	float y_ray = cb->player.y;
// 	float next_x = cb->player.x;
// 	float next_y = cb->player.y;
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

// t_pos ft_calcultae_next_wall_h(t_cub3D *cb)
// {
// 	t_pos next_wall;

//     next_wall.x = cb->player.x + cos(cb->angle * M_PI / 180) * COF_PIXEL / 2;
//     next_wall.y = cb->player.y + sin(cb->angle * M_PI / 180) * COF_PIXEL / 2;
//     return (next_wall);
// }

// t_pos ft_calculate_next_wall_h(t_cub3D *cb)
// {
// 	t_pos wall;
// 	float next_x;
// 	float next_y;
// 	int i;

// 	next_x = cb->player.x + sin(cb->angle * M_PI / 180) * COF_PIXEL / 2;
//     next_y = cb->player.y + cos(cb->angle * M_PI / 180) * COF_PIXEL / 2;
// 	while (is_wall_pixel(cb, next_x, next_y) && next_x > 0 && next_y > 0 && next_x < COF_PIXEL* cb->map.width && next_y < COF_PIXEL* cb->map.height)
// 	{
// 		next_x = next_x + sin(cb->angle * M_PI / 180) * COF_PIXEL / 2;
//         next_y = next_y + cos(cb->angle * M_PI / 180) * COF_PIXEL / 2;
// 	}
// 	printf("the position of the h wall is x[%d] and y[%d]and angle %d\n", (int)next_x, (int)next_y,cb->angle);
// 	wall.x = next_x;//need to be optimited change next_x by wall.x
// 	wall.y = next_y;
// 	return (wall);
// }

int indice_v(int *i,int *check, int angle)
{
	if (angle <= 90 || angle >= 270)
	{
		*i += 1;
		return(*i);
	}	
	else
	{
		if (!(*check))
		{
			*check += 1;
			return(0);
		}
		*i -= 1;
		return(*i);
	}
}

t_pos ft_calculate_next_wall_v(t_cub3D *cb, float angle)
{
	t_pos	wall;
	float x_ray;
	float y_ray;
	float next_x;
	int i = 0;
	int check = 0;
	float next_y;

	next_x = (int)(cb->player.x / COF_PIXEL) * COF_PIXEL + COF_PIXEL*(indice_v(&i,&check, angle));
	next_y = cb->player.y - (cb->player.x - next_x)* tan(angle * M_PI / 180.0);
	while (is_wall_pixel(cb, next_x, next_y)&& next_x > 0 && next_y > 0 && next_x < COF_PIXEL*cb->map.width && next_y < COF_PIXEL*cb->map.height)
	{
		next_x = (int)(cb->player.x / COF_PIXEL) * COF_PIXEL + COF_PIXEL*(indice_v(&i,&check, angle));
		next_y = cb->player.y - (cb->player.x - next_x)* tan(angle * M_PI / 180.0);
	}
    wall.x = next_x;
    wall.y = next_y;
	// printf("the position of the V wall is x[%d = %d] y[%d = %d] angle %d\n", (int)next_y/COF_PIXEL, wall.y, (int)(next_x/COF_PIXEL),wall.x,cb->angle);
	return (wall);
}
// t_pos ft_calculate_next_wall_h(t_cub3D *cb, int angle)
// {
//     t_pos wall;
//     float x_ray;
//     float y_ray;
//     float next_x;
//     int i = 0;
//     float next_y;

//     next_x = cb->player.x + cos(angle * M_PI / 180) * COF_PIXEL / 2;
//     next_y = cb->player.y + sin(angle * M_PI / 180) * COF_PIXEL / 2;

//     while (is_wall_pixel(cb, next_x, next_y) && next_x > 0 && next_y > 0 && next_x < COF_PIXEL * cb->map.width && next_y < COF_PIXEL * cb->map.height)
//     {
//         next_x = next_x + cos(angle * M_PI / 180) * COF_PIXEL / 2;
//         next_y = next_y + sin(angle * M_PI / 180) * COF_PIXEL / 2;
//     }

//     wall.x = next_x;
//     wall.y = (int)(next_y / COF_PIXEL) * COF_PIXEL;

//     printf("the position of the H wall is x[%d = %d] y[%d = %d] angle %d\n", (int)next_x / COF_PIXEL, wall.x, (int)(next_y / COF_PIXEL), cb->angle, wall.y);
    
//     return wall;
// }

// t_pos ft_calculate_next_wall_v(t_cub3D *cb, int angle)
// {
// 	t_pos wall;
// 	int x_ray;
// 	int y_ray;
// 	int next_x;
// 	int i = 0;
// 	int next_y;

// 	// next_x = (int)(cb->player.x / COF_PIXEL) * COF_PIXEL + COF_PIXEL*(++i);
// 	// next_y = cb->player.y + (next_x - cb->player.x)* tan((cb->angle)* M_PI / 180);

// 	next_x = cb->player.x + cos(angle * M_PI / 180) * COF_PIXEL / 2;
//     next_y = cb->player.y + sin(angle * M_PI / 180) * COF_PIXEL / 2;
// 	while (is_wall_pixel(cb, next_x, next_y) && next_x > 0 && next_y > 0 && next_x < COF_PIXEL*cb->map.width && next_y < COF_PIXEL*cb->map.height)
// 	{
// 		next_x = next_x + cos(angle * M_PI / 180) * COF_PIXEL / 2;
//         next_y = next_y + sin(angle * M_PI / 180) * COF_PIXEL / 2;
// 	}
// 	// {
// 	// 	next_x = (int)(cb->player.x / COF_PIXEL) * COF_PIXEL + COF_PIXEL*(++i);
// 	// 	next_y = cb->player.y + (next_x - cb->player.x)* tan((cb->angle)* M_PI / 180);
// 	// }
// 	// wall.x = (int)(next_x/COF_PIXEL)*COF_PIXEL;//convert 
// 	wall.x = next_x;
// 	wall.y = next_y;
// 	printf("the position of the V wall is x[%d = %d] y[%d = %d] angle %d\n", (int)(next_x/COF_PIXEL),wall.x, (int)next_y/COF_PIXEL, wall.y,cb->angle);
// 	return(wall);
// }
int wall_color(t_pos wall, float angle)
{
	if (wall.w == 0 || wall.w == 90)
		return (0xFF0000FF);//S in red color
	else if(wall.w == 180 || wall.w == 270)
		return (0x00FF00FF);//N in green color
	else if (wall.w == 10 || wall.w == 1270)
		return (0x0000FFFF);//E in blue color
	else if (wall.w == 190 || wall.w == 1180)
		return (0x800080FF);//W in porpul color
	return (0x000000FF);
}
	// if (an)
	// {
	// 	if (wall.w)
	// 		return (0x000000FF);
	// 	else
	// 		return (0xFFFFFFFF);
	// }
	// else if (angle > 90 || angle < 180)
	// {
	// 	if (wall.w)
	// 		return (0x000000FF);
	// 	else
	// 		return (0xFFFFFFFF);
	// }
	// else if (angle > 0 || angle < 270)
	// {
	// 	if (wall.w)
	// 		return (0x000000FF);
	// 	else
	// 		return (0xFFFFFFFF);
	// }
	// else
	// {
	// 	if (wall.w)
	// 		return (0x000000FF);
	// 	else
	// 		return (0xFFFFFFFF);
	// }

void draw_3d(t_cub3D *cb)
{
			float i = -1;
		float starta = -AGNGLE_VUE/2;
	while(++i < WINDOW_WIDTH)
	{
		float angle = (i*AGNGLE_VUE)/WINDOW_WIDTH + starta + cb->angle;
		// if (angle + starta <= 0)
		// 	angle = angle + 360;
		// angle = (angle + 360) % 360;
		t_pos wall = ft_calculate_next_wall(cb, angle);//*(AGNGLE_VUE/WINDOW_WIDTH));
		int dist = dis(cb, wall);
		int line_hight = WINDOW_HEIGHT / dist * 1;
		if(line_hight > WINDOW_HEIGHT)
			line_hight = WINDOW_HEIGHT;
		int start = (WINDOW_HEIGHT /2 ) - line_hight / 2;
		// printf("dis = %d, line_hight = %d, start = %d i: %d\n", dist, line_hight, start, i);
		mlx_draw_line(cb, i, 0, i, line_hight, 0x000000FF);
		draw_line(cb->img, i, start, i ,start + line_hight, wall_color(wall, angle));//! 3d lines 
		draw_line(cb->img, cb->player.x, cb->player.y, wall.x, wall.y, 0x000000FF);//raise in mini maps lines
	}	
}
void	map(void *v)
{
	t_cub3D	*cb;

	cb = v;
	draw_C_F(cb);
	// walls(cb);
	draw_map(cb);
	// draw_player(cb, COF_PIXEL / 8, cb->angle);
	// draw_3d(cb);
		// -AGNGLE_VUE/2;
	// while(i < AGNGLE_VUE/2)
	// {
		
	// }
}

int indice_h(int *i,int *check, float angle,int option)
{
	if (!option)
	{
		if (angle <= 180)
		{
			*i += 1;
			return(*i);
		}	
		else
		{
			if (!(*check))
			{
				*check += 1;
				return(0);
			}
			*i -= 1;
			return(*i);
		}
	}
	else
	{
		if (angle > 90 || angle < 270)
			return (1);
		else
			return (-1);
	}
}

t_pos ft_calculate_next_wall_h(t_cub3D *cb, float angle)
{
	t_pos	wall;
	float x_ray;
	float y_ray;
	float next_x;
	int check = 0;
	int i = 0;
	float next_y;

	next_y = (int)(cb->player.y / COF_PIXEL) * COF_PIXEL + COF_PIXEL*(indice_h(&i, &check, angle, 0));
	next_x = cb->player.x + (next_y - cb->player.y)/tan(angle * M_PI / 180.0*(indice_h(&i, &check, angle, 1)));
	while (is_wall_pixel(cb, next_x, next_y)&& next_x > 0 && next_y > 0 && next_x < COF_PIXEL*cb->map.width && next_y < COF_PIXEL*cb->map.height)
	{
		next_y = (int)(cb->player.y / COF_PIXEL) * COF_PIXEL + COF_PIXEL*(indice_h(&i, &check, angle, 0));
		next_x = cb->player.x + (next_y - cb->player.y)/tan(angle * M_PI / 180.0)*(indice_h(&i, &check, angle, 1));
	}
    wall.x = next_x;
    wall.y = next_y; 
	// printf("the position of the H wall is x[%d = %d] y[%d = %d] angle %d\n", (int)next_y/COF_PIXEL, wall.y, (int)(next_x/COF_PIXEL),wall.x,cb->angle);
	return (wall);
}

float dis(t_cub3D *cb,t_pos a)
{
	t_pos c;
	float d;

	c.x = cb->player.x;
	c.y = cb->player.y;
	d = sqrt((c.x - a.x)*(c.x - a.x) + (c.y - a.y)*(c.y - a.y));
	return(d);
}

t_pos ft_min(t_cub3D *cb, t_pos a,t_pos b)
{
	t_pos c;

	c.x = cb->player.x;
	c.y = cb->player.y;
	if (dis(cb, a) < dis(cb, b))
	{
		if(cb->angle <= 90)
			a.w = 0;
		else if(cb->angle <= 180)
			a.w = 90;
		else if(cb->angle <= 270)
			a.w = 180;
		else
			a.w = 270;
		return(a);
	}
	else
	{
		if(cb->angle <= 90)
			b.w = 10;
		else if(cb->angle <= 180)
			b.w = 190;
		else if(cb->angle <= 270)
			b.w = 1180;
		else
			b.w = 1270;	
		return(b);
	}
}

t_pos ft_calculate_next_wall(t_cub3D *cb,float angle)
{
	return(ft_min(cb ,ft_calculate_next_wall_h(cb, angle),ft_calculate_next_wall_v(cb, angle)));
	// return(ft_calculate_next_wall_v(cb, angle));
}

//! this function is used to change player angle
void change_angle(t_cub3D *cb, int KEY)
{
	if (KEY == MLX_KEY_RIGHT)
	{
		cb->angle += 0.02;
		if (cb->angle >= 2 * M_PI)
			cb->angle -= 2 * M_PI;
	}
	else if (KEY == MLX_KEY_LEFT)
	{
		cb->angle -= 0.02;
		if (cb->angle < 0)
			cb->angle += 2 * M_PI;
	}
	/*if (KEY == MLX_KEY_RIGHT && (cb->angle) <= 360 - ANGLE_MOV)
		cb->angle = (cb->angle + ANGLE_MOV) % 360;
	else if (KEY ==  MLX_KEY_LEFT && cb->angle >= ANGLE_MOV)
		cb->angle = (cb->angle - ANGLE_MOV) % 360;
	else if (cb->angle == 0 && KEY == MLX_KEY_LEFT)
		cb->angle = 360 - ANGLE_MOV;*/
	// else
	// 	cb->angle = 350;
	// draw_C_F(cb);
	// map(cb);
	// walls(cb);
	// ft_calculate_next_wall(cb);
	// ft_calculate_next_wall_v(cb);
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
}
