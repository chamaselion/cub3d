/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:43:19 by alima             #+#    #+#             */
/*   Updated: 2025/06/24 23:30:02 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	whitespaces(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\n')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	read_map(t_game *g, char *map)
{
	char	*read;

	if (ft_strlen(map) <= 4 || ft_strncmp(map + (ft_strlen(map) - 4), ".cub",
			4))
		err_exit_msg("Map name must end with .cub");
	g->map_fd = open(map, O_RDONLY);
	if (g->map_fd < 0)
		err_exit_msg("Couldn't open the map!");
	load_config(g);
	read = get_next_line(g->map_fd);
	while (whitespaces(read) == 0)
	{
		free(read);
		read = get_next_line(g->map_fd);
	}
	fill_map(g, read);
}

void	fill_map(t_game *game, char *reader)
{
	int	y;

	y = 0;
	game->map = ft_calloc(300, sizeof(char *));
	while (reader)
	{
		game->map[y++] = ft_strdup(reader);
		free(reader);
		reader = get_next_line(game->map_fd);
		game->height_map++;
	}
	while (y-- > 0 && whitespaces(game->map[y]) == 0)
	{
		free(game->map[y]);
		game->map[y] = NULL;
		game->height_map--;
	}
}
// too long
//  void	fill_map(t_game *game, char *reader)
//  {
//  	int	y;

// 	y = 0;
// 	game->map = ft_calloc(300, sizeof(char *));
// 	if (!game->map)
// 		exit(1);
// 	while (reader != NULL)
// 	{
// 		game->map[y] = ft_strdup(reader);
// 		free(reader);
// 		reader = get_next_line(game->map_fd);
// 		y++;
// 		game->height_map++;
// 	}
// 	y -= 1; // start checking from last line
// 	while (y >= 0)
// 	{
// 		if (whitespaces(game->map[y]) == 0)
// 		{
// 			free(game->map[y]);
// 			game->map[y] = NULL;
// 			game->height_map--;
// 		}
// 		else
// 			break ;
// 		y--;
// 	}
// }

void	find_width(t_game *game)
{
	int	x;
	int	y;
	int	tmp;

	y = 0;
	tmp = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
			x++;
		while (game->map[y][x - 1] == ' ' || game->map[y][x - 1] == '\n')
			x--;
		if (x > tmp)
			tmp = x;
		y++;
	}
	game->width_map = tmp;
}
