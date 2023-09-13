/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ban.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:17:13 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/09/12 19:4 by yaidriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

float angle_overlap(float angle)
{
	if (angle < 0)
		angle+=2*M_PI;
	else if (angle > 2*M_PI)
		angle-=2*M_PI;
	return (angle);
}

int wall_side(t_cub3D *cb, float angle, int side)
{
	if(!side)
	{
		if (angle > M_PI)
			return(0x00FF00FF);//color is black
			// return (cb->texture[EA].img[(int)cb->texture[EA].width * (int)(angle * (cb->texture[EA].height / (2 * M_PI)))]);
		else
			return(0x0000FFFF);//color is green
			// return (cb->texture[WE].img[(int)cb->texture[WE].width * (int)(angle * (cb->texture[WE].height / (2 * M_PI)))]);
	}
	else
	{
		if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
			return(0xcc0000FF);//color is blue
			// return (cb->texture[SO].img[(int)cb->texture[SO].width * (int)(angle * (cb->texture[SO].height / (2 * M_PI)))]);
		else
			return(0xc0ccccFF);//color is yellow
			// return (cb->texture[NO].img[(int)cb->texture[NO].width * (int)(angle * (cb->texture[NO].height / (2 * M_PI)))]);
	}
}

void	test(void *param)
{
	t_cub3D  *cb = param;
	float hx;
	float hy;
	float vx;
	float vy;
	float ra;
	int rc;
	float hyblock;
	float hxblock;
	float vxblock;
	float vyblock;
	float angle_step;
	float atan;
	int x = cb->player.x;
	int y = cb->player.y;
	int i = -1;
	float rx,ry;
	float dis_w ;
	int m_width = cb->map.width*COF_PIXEL;
	int m_height = cb->map.height*COF_PIXEL;
	// printf("the width is %d and the height is %d\n",m_width,m_height);
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
		while (hy < m_height && hy > 0)// WINDOW_HEIGHT && hy > 0)
		{
			if (hx > m_width || hx < 0)//WINDOW_WIDTH + 1000 || hx < 0)
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

		while (vx < m_width && vx > 0) // WINDOW_WIDTH + 1000 && vx > 0)
		{
			// printf("x[%d] y[%d]  c[%c]\n", (int)hx / COF_PIXEL, (int)hy / COF_PIXEL, cb->map.map_tmp[(int)hy / COF_PIXEL][(int)hx / COF_PIXEL]);
			if (vy > m_height || vy < 0)// WINDOW_HEIGHT || vy < 0)
				break ;
			else if (!is_wall_pixel(cb, vx, vy))
				break ;
			vx += vxblock;
			vy += vyblock;
		}
		
		float dis_h = sqrt((hx - x) * (hx - x) + (hy - y) * (hy - y));
		float dis_v = sqrt((vx - x) * (vx - x) + (vy - y) * (vy - y));
		if (dis_h < dis_v)
		{
			dis_w = dis_h;
			rx = hx;
			ry = hy;
			rc = 0;
		}
		else
		{
			dis_w = dis_v;
			rx = vx;
			ry = vy;
			rc = 1;
		}
		
		// printf("hx[%f] hy[%f]\n",hx,hy);
		//printf("x[%f] y[%f]  vx[%f] vy[%f]\n", x, y, vx, vy);
		dis_w = cos(((AGNGLE_VUE / 2) *M_PI/180) - (i * angle_step)) * dis_w;
		float Projection_to_wall = ((float)WINDOW_HEIGHT/4)/-tan(30) * ((float)WINDOW_HEIGHT/dis_w);
		Projection_to_wall *= 2; //wall is square 
		if (Projection_to_wall > WINDOW_HEIGHT)
			Projection_to_wall = WINDOW_HEIGHT;
		draw_line(cb->img2, x/4, y/4, rx/4, ry/4, 0x000000FF);//line draw
		int y_wall = WINDOW_HEIGHT/2-(Projection_to_wall/2);
		// draw_line(cb->img, i, y_wall, i, y_wall + Projection_to_wall, 0x0000ffFF);//line draw
		while (y_wall < WINDOW_HEIGHT/2+(Projection_to_wall/2))
		{
			mlx_put_pixel(cb->img, i, y_wall, wall_side(cb, ra,rc));
			y_wall++;
		}
		ra += angle_step;
	}
}