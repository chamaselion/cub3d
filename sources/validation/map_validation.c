/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:37 by alima             #+#    #+#             */
/*   Updated: 2025/06/26 17:15:37 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_player_number(t_game *g, int nb)
{
	if (nb == 0)
	{
		printf("No player character found\n");
		free(g->start);
		exit(EXIT_FAILURE);
	}
	if (nb > 1)
	{
		printf("Multiple player characters found\n");
		free(g->start);
		exit(EXIT_FAILURE);
	}
}

// static void	free_map(t_game *game)
// {
// 	int	i;

// 	if (!game->map)
// 		return ;
// 	i = 0;
// 	while (i < game->height_map)
// 	{
// 		if (game->map[i])
// 			free(game->map[i]);
// 		i++;
// 	}
// 	free(game->map);
// 	game->map = NULL;
// }


void find_player_pos(t_game *g)
{
	int	x;
	int	y;
	int	nb;

	y = -1;
	nb = 0;
	g->start = malloc(sizeof(int) * 2);
	while (g->map[++y] != NULL)
	{
		x = -1;
		while (g->map[y][++x] != '\0')
		{
			if (ft_isalpha(g->map[y][x]))
			{
				if (is_player(g->map[y][x])) // Check return value
				{
					g->pos = g->map[y][x];	
					g->start[0] = y;
					g->start[1] = x;
					nb++;
				}
			}
		}
	}
	check_player_number(g, nb);
}

void	validate_map(t_game *g)
{
	find_width(g);
	find_player_pos(g);
	check_sides(g, g->start[0], g->start[1]);
	valid_walls(g, g->map, g->start[0], g->start[1]);
	// normalize_spaces(g);
}