/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:56:45 by yaidriss          #+#    #+#             */
/*   Updated: 2023/08/24 11:24:49 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// int	find_path_map(char **mp)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (mp[++i])
// 	{
// 		j = -1;
// 		while (mp[i][++j])
// 		{
// 			if (mp[i][j] == 'C' || mp[i][j] == 'E' || mp[i][j] == 'P')
// 				return (0);
// 		}
// 	}
// 	return (1);
// }

// int	test_valid_map(t_map *map)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < map->width && !find_path_map(map->map2))
// 	{
// 		test_down(map);
// 		test_up(map);
// 	}
// 	return (1);
// }

// void	test_down(t_map *map)
// {
// 	int		i;
// 	int		j;
// 	char	**mp;

// 	mp = map->map2;
// 	i = 0;
// 	while (++i < map->hight)
// 	{
// 		j = -1;
// 		while (mp[i][++j])
// 			if (mp[i][j] == 'V' || mp[i][j] == 'P')
// 				change_neighbor(mp, i, j);
// 	}
// }

// void	test_up(t_map *map)
// {
// 	int		i;
// 	int		j;
// 	char	**mp;

// 	mp = map->map2;
// 	i = map->hight - 1;
// 	while (--i > 0)
// 	{
// 		j = map->width - 1;
// 		while (mp[i][--j])
// 			if (mp[i][j] == 'V' || mp[i][j] == 'P')
// 				change_neighbor(mp, i, j);
// 	}
// }

// t_loc	*position(int i, int j)
// {
// 	t_loc	*pos;

// 	pos = NULL;
// 	pos->x = i;
// 	pos->y = j;
// 	return (pos);
// }
