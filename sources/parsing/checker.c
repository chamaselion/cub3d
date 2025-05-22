/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:22:17 by alima             #+#    #+#             */
/*   Updated: 2025/05/22 16:34:37 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_map_width(t_game *game)
{
	int	x;
	int	y;
	int	temp;

	y = 0;
	temp = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			x++;
		}
		while (game->map[y][x - 1] == ' ' || game->map[y][x - 1] == '\n')
			x--;
		if (x > temp)
			temp = x;
		y++;
	}
	game->width_map = temp;
}
void	check_walls(char **map, int x, int y, t_game *game)
{
	
}
void	check_validity(t_game *game)
{
	int	checker;

	checker = 0;
	checker = check_row_lengths(game);
	checker = check_rectangular(game);
	checker = check_walls(game);
	if (checker == 1)
	{
		free(game->map);
		finish(0);
	}
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

int	check_row_lengths(t_game *game)
{
	int	expected_len;
	int	y;

	expected_len = ft_strlen(game->map[0]);
	y = 1;
	while (y < game->height_map - 1)
	{
		if ((int)ft_strlen(game->map[y]) != expected_len)
		{
			ft_printf("Error! Map rows are not the same length.\n");
			return (1);
		}
		y++;
	}
	return (0);
}

// int	check_rectangular(t_game *game)
// {
// 	size_t	row_len;

// 	if (game->height_map < 1)
// 		return (1);
// 	row_len = ft_strlen(game->map[0]);
// 	row_len--;
// 	if (row_len == (size_t)game->height_map)
// 	{
// 		ft_printf("Error! Map must not be square.\n");
// 		return (1);
// 	}
// 	return (0);
// }

void	check_path(t_game *game, int new_y, int new_x, char c)
{
	game->steps++;
	if (game->map[new_x][new_y] == 'C')
	{
		game->col_count--;
		game->map[new_x][new_y] = '0';
	}
	if (game->map[new_x][new_y] == '1' || (game->map[new_x][new_y] == 'E'
			&& game->col_count != 0))
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