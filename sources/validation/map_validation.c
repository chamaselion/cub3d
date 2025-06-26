/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:37 by alima             #+#    #+#             */
/*   Updated: 2025/06/26 23:27:03 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_player_number(int nb)
{
	if (nb == 0)
		err_exit_msg("No player character found");
	if (nb > 1)
		err_exit_msg("Multiple player characters found");
}

void	find_player_pos(t_game *g)
{
	int	x;
	int	y;
	int	nb;

	y = -1;
	nb = 0;
	while (g->map[++y] != NULL)
	{
		x = -1;
		while (g->map[y][++x] != '\0')
		{
			if (ft_isalpha(g->map[y][x]))
			{
				if (is_player(g->map[y][x]))
				{
					g->pos = g->map[y][x];
					g->player.y = y;
					g->player.x = x;
					nb++;
				}
			}
		}
	}
	check_player_number(nb);
}

void	validate_map(t_game *g)
{
	char	**map_copy;
	int		i;
	int		len;

	find_width(g);
	find_player_pos(g);
	check_sides(g, g->player.y, g->player.x);
	i = 0;
	while (g->map[i] != NULL)
		i++;
	map_copy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (g->map[i] != NULL)
	{
		len = ft_strlen(g->map[i]);
		map_copy[i] = malloc(sizeof(char) * (len + 1));
		ft_memcpy(map_copy[i], g->map[i], len + 1);
		i++;
	}
	map_copy[i] = NULL;
	valid_walls(g, map_copy, g->player.y, g->player.x);
	free_char_array(map_copy);
}
