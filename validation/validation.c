/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:57:01 by yaidriss          #+#    #+#             */
/*   Updated: 2023/09/11 09:23:15 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/* chek bol to see if there is something other than NO SO WE EA F C before arriving to the map*/
void	check_bol(t_cub3D *cb)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (cb->text[i].bol != 1)
			handl_errors(10);
	i = -1;
	while (++i < 2)
		if (cb->colors[i].bol != 1)
			handl_errors(10);
}

/*check player if its repeated or it doesnt exist*/
void	check_repeat(t_cub3D *cb)
{
	int	i;

	i = -1;
	while (cb->joined_map[++i])
	{
		if (cb->joined_map[i] == 'N' || cb->joined_map[i] == 'S'
			|| cb->joined_map[i] == 'W' || cb->joined_map[i] == 'E')
			cb->p++;
		else if (cb->joined_map[i] != '1' && cb->joined_map[i] != '0'
				&& cb->joined_map[i] != ' ' && cb->joined_map[i] != '\t'
				&& cb->joined_map[i] != '\n')
		{
			free(cb->joined_map);
			handl_errors(10);
		}
	}
	if (cb->p != 1)
	{
			free(cb->joined_map);
			handl_errors(10);
	}
}

void	check_all_sides(char **str, int x, int y)
{
	if (str[y][x] != '1' && str[y][x] != '0'
		&& str[y][x] != 'N' && str[y][x] != 'S'
		&& str[y][x] != 'W' && str[y][x] != 'E')
	{
		ft_free_float(str);
		handl_errors(10);
	}
}

/* store player position and check if 0 or player are surrounded by other than 1 and 0  */
//! when i put the player  to W character the forme of the player is changed we need to check this errurs

int	p_or_z(t_cub3D *cb, char c, int x, int y)
{
	if (c == '0')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		cb->player.x = x * COF_PIXEL;
		cb->player.y = y * COF_PIXEL;
		if (c == 'N')
			cb->angle = (3 * M_PI) / 2;
		else if(c == 'S')
			cb->angle = M_PI / 2;
		else if(c == 'E')
			cb->angle = 0;
		else if (c == 'W')
			cb->angle = M_PI;
		return (1);
	}
	return (0);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	check_valid_map(t_cub3D *cb)
{
	int	x;
	int	y;

	y = -1;
	cb->map.height = 0;
	cb->map.width = 0;
	while (cb->map.map_tmp[++y])
	{
		x = 0;
		while (cb->map.map_tmp[y][x])
		{
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y))
				check_all_sides(cb->map.map_tmp, x - 1, y);
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y))
				check_all_sides(cb->map.map_tmp, x + 1, y);
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y))
				check_all_sides(cb->map.map_tmp, x, y - 1);
			if (p_or_z(cb, cb->map.map_tmp[y][x], x, y))
				check_all_sides(cb->map.map_tmp, x, y + 1);
			x++;
		}
		cb->map.width = ft_max(cb->map.width, x);
		cb->map.height++;
	}
}


int	check_content(t_cub3D *cb)
{
	cb->line = get_next_line(cb->fd);
	while (cb->line)
	{
		if (fill_type(cb))
		{
			printf("im here check inside if fill_type\n");
			free(cb->line);
			handl_errors(6);
		}
		free(cb->line);
		cb->line = get_next_line(cb->fd);
	}
	// close(cb->fd);
	free(cb->line);
	check_bol(cb);
	check_repeat(cb);
	cb->map.map_tmp = ft_split(cb->joined_map, '\n');
	free(cb->joined_map);
	check_valid_map(cb);
	return (0);
}

// void init_cub3D(t_cub3D *cb)
// {
// 	return;
// 	// cb.map = init_map(fd);
// }

// void	fill_map(t_map *map)
// {
// 	char	*buffer;
// 	char	*buffer2;
// 	int		i;

// 	i = -1;
// 	map->next = (char *)1;
// 	buffer = NULL;
// 	while (map->next)
// 	{
// 		map->next = get_next_line(map->fd);
// 		buffer = ft_my_strjoin(buffer, map->next, 1);
// 	}
// 	while (buffer[++i])
// 		if (buffer[0] == '\n' || (buffer[i] == '\n' && buffer[i + 1] == '\n'))
// 			handl_errors(3);
// 	buffer2 = ft_strdup(buffer);
// 	map->map = ft_split(buffer, '\n');
// 	if (!map->map[0])
// 		handl_errors(3);
// 	map->map2 = ft_split(buffer2, '\n');
// 	free(buffer);
// 	free(buffer2);
// }

// void	test_rectangular(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	map->hight = 0;
// 	while (map->map[map->hight])
// 		map->hight++;
// 	map->width = ft_strlen(map->map[0]);
// 	while (map->map[i])
// 		if (ft_strlen(map->map[i++]) == map->width)
// 			j++;
// 	if (j != map->hight)
// 		handl_errors(3);
// }

// void	test_walls(t_map *map)
// {
// 	int	i;

// 	i = -1;
// 	while (map->map[0][++i])
// 		if (map->map[0][i] != '1' || map->map[map->hight - 1][i] != '1')
// 			handl_errors(3);
// 	i = -1;
// 	while (++i < map->hight)
// 		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
// 			handl_errors(3);
// }

// void	test_caraters(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	map->count_p = 0;
// 	map->count_e = 0;
// 	map->count_c = 0;
// 	while (++i < map->hight)
// 	{
// 		j = -1;
// 		while (map->map[i][++j])
// 		{
// 			if (map->map[i][j] == 'P')
// 				map->count_p++;
// 			else if (map->map[i][j] == 'C')
// 				map->count_c++;
// 			else if (map->map[i][j] == 'E')
// 				map->count_e++;
// 			else if (map->map[i][j] != '0' && map->map[i][j] != '1')
// 				handl_errors(1);
// 		}
// 	}
// 	if (map->count_p != 1 || map->count_e != 1 || map->count_c < 1)
// 		handl_errors(9);
// }
//!need to set the postion of all character ( Player and exit)

// void	change_neighbor(char **mp, int i, int j)
// {
// 	if (mp[i][j - 1] != 'V' && mp[i][j - 1] != '1')
// 				mp[i][j - 1] = 'V';
// 	if (mp[i][j + 1] != 'V' && mp[i][j + 1] != '1')
// 				mp[i][j + 1] = 'V';
// 	if (mp[i + 1][j] != 'V' && mp[i + 1][j] != '1')
// 				mp[i + 1][j] = 'V';
// 	if (mp[i - 1][j] != 'V' && mp[i - 1][j] != '1')
// 				mp[i - 1][j] = 'V';
// }
