/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:45:27 by alima             #+#    #+#             */
/*   Updated: 2025/06/19 16:51:11 by alima            ###   ########.fr       */
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
