/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:17 by alima             #+#    #+#             */
/*   Updated: 2025/06/06 22:39:06 by alima            ###   ########.fr       */
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
int check_near(t_game *game, int y, int x)
{
	if (y > 0 && !is_wall(game->map[y-1][x]) && !is_empty(game->map[y-1][x]))
		return (1);
	if (y < game->height_map - 1 && !is_wall(game->map[y+1][x]) && !is_empty(game->map[y+1][x]))
		return (1);
	if (x > 0 && !is_wall(game->map[y][x-1]) && !is_empty(game->map[y][x-1]))
		return (1);
	if (x < game->width_map - 1 && !is_wall(game->map[y][x+1]) && !is_empty(game->map[y][x+1]))
		return (1);
	return (0);
}

int check_interior(t_game *game)
{
	int x;
	int y;

	y = 1;
	while (y < game->height_map - 1)
	{
		x = 1;
		while (x < game->width_map - 1)
		{
			if (!is_valid_char(game->map[y][x]))
				return (printf("Error! Invalid char at %d,%d\n", x, y), 1);
			if (is_empty(game->map[y][x]) && check_near(game, y, x))
				return (printf("Error! Unenclosed space at %d,%d\n", x, y), 1);
			x++;
		}
		y++;
	}
	return (0);
}

int check_walls(t_game *game)
{
	if (check_top_bottom(game))
		return (1);
	if (check_sides(game))
		return (1);
	if (check_interior(game))
		return (1);
	return (0);
}

void normalize_spaces(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->height_map)
	{
		x = 0;
		while (x < game->width_map)
		{
			if (game->map[y][x] == ' ')
				game->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int check_player_number(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	int counter = 0;
	while (y < game->height_map)
	{
		x = 0;
		while (x < game->width_map)
		{
			if (game->map[y][x] == 'W' ||
				game->map[y][x] == 'N' ||
				game->map[y][x] == 'S' ||
				game->map[y][x] == 'E')
				counter++;
			x++;
		}
		y++;
	}
	if (counter == 1)
		return (0);
	return (1);
}
void check_validity(t_game *game)
{
	int checker;

	checker = check_walls(game);
	checker += check_player_number(game);
	if (checker != 0)
	{
		printf("Map validation failed\n");
		// free_map(game); to do
		exit(EXIT_FAILURE);
	}
}

void validate_map(t_game *game)
{
	normalize_spaces(game);  // Convert spaces to '0'
	check_validity(game);
}
