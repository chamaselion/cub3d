/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:37 by alima             #+#    #+#             */
/*   Updated: 2025/06/19 16:53:50 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
