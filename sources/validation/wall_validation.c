/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:17 by alima             #+#    #+#             */
/*   Updated: 2025/06/26 23:27:34 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_sides(t_game *g, int y, int x)
{
	if (y == 0 || x == 0)
		err_exit_msg("Walls are not closed!");
	if (y + 1 >= g->height_map)
		err_exit_msg("Walls are not closed!");
}

void	valid_walls(t_game *g, char **map, int y, int x)
{
	if (y < 0 || y >= g->height_map
		|| x < 0 || x >= g->width_map + 1)
		return ;
	if (map[y][x] == '1')
		return ;
	if ((map[y][x] == '0')
		&& ((y - 1 == -1 || x - 1 == -1
		|| y == g->height_map - 1)))
		err_exit_msg("Walls are not closed!");
	if (map[y][x] == ' ' || g->map[y][x] == '\n')
		err_exit_msg("Walls are not closed!");
	map[y][x] = '1';
	valid_walls(g, map, y - 1, x);
	valid_walls(g, map, y + 1, x);
	valid_walls(g, map, y, x - 1);
	valid_walls(g, map, y, x + 1);
}
