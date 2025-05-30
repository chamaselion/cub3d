/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:09:56 by bszikora          #+#    #+#             */
/*   Updated: 2025/05/30 14:59:03 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

# define WIDTH 1000
# define HEIGHT 1000
# define CEILING_COLOR 0x303030FF
# define FLOOR_COLOR 0x606060FF
# define WALL_NORTH 0x0000FFFF
# define WALL_SOUTH 0x00FF00FF
# define WALL_EAST 0xFFFFFFFF
# define WALL_WEST 0xFF0000FF
# define MOVESPEED 0.05
# define ROTSPEED 0.05
# define EAST 0
# define NORTH M_PI_2
# define WEST M_PI
# define SOUTH 4.71238898038469 // Approximation of 3 * π / 2

typedef struct s_keys
{
	bool	d;
	bool	s;
	bool	a;
	bool	w;
	bool	left;
	bool	right;
}				t_keys;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	float		px;
	float		dx;
	float		plx;
	float		py;
	float		dy;
	float		ply;
	t_keys		keys;
	char		**map;
}				t_data;

typedef struct s_update_vars
{
    int			x, y;
    double		cx, rx, ry;
    int			mx, my;
    double		sdx, sdy;
    double		ddx, ddy;
    int			stepx, stepy;
    int			hit, side;  // side: 0 = NORTH, 1 = SOUTH, 2 = EAST, 3 = WEST
    double		pwd;
    int			lh, ds, de;
    uint32_t	col;
}				t_update_vars;

typedef struct s_player
{
	int			x;
	int			y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	char		**map;
	int			map_fd;
	int			x;
	int			y;
	int			height_map;
	int			width_map;
	t_player	player;
}				t_game;

void			move_player(t_data *d, float mx, float my);
void			rotate(t_data *d, float rs);
void			key_hook(mlx_key_data_t kd, void *param);
void			update(void *param);
// we need this function
// char	*get_next_line(int fd);

// added 
// parsing.c
int		whitespaces(char *str);
void	read_map(t_game *game, char *map);
void	fill_map(t_game *game, char *reader);
void	find_width(t_game *game);
// added
char	*trim_map_line(char *line);

// checker.c
int	check_walls(t_game *game);
void	check_validity(t_game *game);
#endif