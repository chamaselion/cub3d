/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:41:37 by alima             #+#    #+#             */
/*   Updated: 2025/06/27 12:47:30 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**allocate_map_copy(t_game *g)
{
	char	**map_copy;
	int		i;

	i = 0;
	while (g->map[i] != NULL)
		i++;
	map_copy = malloc(sizeof(char *) * (i + 1));
	if (!map_copy)
		err_exit_msg("Memory allocation failed");
	return (map_copy);
}

void	copy_map_line(char **map_copy, t_game *g, int i)
{
	int	len;
	int	j;

	len = ft_strlen(g->map[i]);
	map_copy[i] = malloc(sizeof(char) * (len + 1));
	if (!map_copy[i])
	{
		j = i;
		while (--j >= 0)
			free(map_copy[j]);
		free(map_copy);
		err_exit_msg("Memory allocation failed");
	}
	ft_memcpy(map_copy[i], g->map[i], len + 1);
}

char	**create_map_copy(t_game *g)
{
	char	**map_copy;
	int		i;

	map_copy = allocate_map_copy(g);
	i = 0;
	while (g->map[i] != NULL)
	{
		copy_map_line(map_copy, g, i);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	validate_map(t_game *g)
{
	char	**map_copy;

	find_width(g);
	find_player_pos(g);
	check_sides(g, g->player.y, g->player.x);
	map_copy = create_map_copy(g);
	valid_walls(g, map_copy, g->player.y, g->player.x);
	free_char_array(map_copy);
}
