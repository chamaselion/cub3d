/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:17 by alima             #+#    #+#             */
/*   Updated: 2025/06/26 16:58:05 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	check_sides(t_game *g, int x, int y)
{
	if (x == 0 || y == 0)
		err_exit_msg("Walls are not closed!\n");
	if (x + 1 >= g->height_map)
		err_exit_msg("Walls are not closed!\n");
}

void	valid_walls(t_game *g, char **map, int x, int y)
{
	if (x < 0 || x >= g->height_map
		|| y < 0 || y >= g->width_map + 1)
		return ;
	if (map[x][y] == '1')
		return ;
	if ((map[x][y] == '0' || map[x][y] == '2' || map[x][y] == '3')
		&& ((x - 1 == -1 || y - 1 == -1
		|| x == g->height_map - 1)))
	{
		printf("Walls are not closed!\n");
		exit(EXIT_FAILURE);
	}
	if (map[x][y] == ' ' || g->map[x][y] == '\n')
	{
		printf("Walls are not closed!\n");
		exit(EXIT_FAILURE);
	}
	map[x][y] = '1';
	valid_walls(g, map, x - 1, y);
	valid_walls(g, map, x + 1, y);
	valid_walls(g, map, x, y - 1);
	valid_walls(g, map, x, y + 1);
}

// int	check_walls(t_game *game)
// {
// 	if (check_top_bottom(game))
// 		return (1);
// 	if (check_sides(game))
// 		return (1);
// 	if (check_interior(game))
// 		return (1);
// 	return (0);
// }
