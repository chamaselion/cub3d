/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:17 by alima             #+#    #+#             */
/*   Updated: 2025/05/22 17:53:43 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < game->width_map)
	{
		if (game->map[0][x] != '1' || game->map[game->height_map
			- 1][x++] != '1')
		{
			ft_printf("Error! Map not sourrounded by walls!\n");
			return (1);
		}
	}
	while (y < game->height_map)
	{
		if (game->map[y][0] != '1' || game->map[y++][game->width_map
			- 1] != '1')
		{
			ft_printf("Error! Map not sourrounded by walls!\n");
			return (1);
		}
	}
	return (0);
}

// 'E' - exit if we are going to the bonus part
void	check_path(t_game *game, int new_y, int new_x, char c)
{
	game->steps++;
	if (game->map[new_x][new_y] == '1' || (game->map[new_x][new_y] == 'E'))
	{
		if (c == 'w')
			game->player.y += 1;
		else if (c == 's')
			game->player.y -= 1;
		else if (c == 'a')
			game->player.x += 1;
		else if (c == 'd')
			game->player.x -= 1;
		game->steps--;
		return ;
	}
	keep_checking(game, new_y, new_x);
}

void	check_validity(t_game *game)
{
	int	checker;

	checker = 0;
	checker = check_walls(game);
	if (checker == 1)
	{
		free(game->map);
		finish(0);
	}
}
