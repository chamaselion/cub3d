/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:17 by alima             #+#    #+#             */
/*   Updated: 2025/06/06 21:43:24 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' ||
			c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int is_wall(char c)
{
	return (c == '1');
}

int is_empty(char c) // is passable path
{
	return (c == '0' || c == ' ' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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
			printf("Error! Map not sourrounded by walls!\n");
			return (1);
		}
	}
	while (y < game->height_map)
	{
		if (game->map[y][0] != '1' || game->map[y++][game->width_map
			- 1] != '1')
		{
			printf("Error! Map not sourrounded by walls!\n");
			return (1);
		}
	}
	return (0);
}


void check_validity(t_game *game)
{
	int checker;

	checker = check_walls(game);
	if (checker != 0)
	{
		printf("Map validation failed\n");
		// free_map(game); to do
		exit(EXIT_FAILURE);
	}
}
