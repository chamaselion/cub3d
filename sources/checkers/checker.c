/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:17 by alima             #+#    #+#             */
/*   Updated: 2025/06/06 21:52:05 by alima            ###   ########.fr       */
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


int check_top_bottom(t_game *game)
{
	int x;

	x = 0;
	while (x < game->width_map)
	{
		if (!is_wall(game->map[0][x]))
			return (printf("Error! Top wall not solid\n"), 1);
		if (!is_wall(game->map[game->height_map - 1][x]))
			return (printf("Error! Bottom wall not solid\n"), 1);
		x++;
	}
	return (0);
}

int check_sides(t_game *game)
{
	int y;

	y = 0;
	while (y < game->height_map)
	{
		if (!is_wall(game->map[y][0]))
			return (printf("Error! Left wall not solid\n"), 1);
		if (!is_wall(game->map[y][game->width_map - 1]))
			return (printf("Error! Right wall not solid\n"), 1);
		y++;
	}
	return (0);
}

int	check_walls(t_game *game)
{
	if (check_top_bottom(game))
		return (1);
	if (check_sides(game))
		return (1);
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
