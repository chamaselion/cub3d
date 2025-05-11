/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:09:56 by bszikora          #+#    #+#             */
/*   Updated: 2025/02/19 12:13:15 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080
# define CEILING_COLOR 0x303030FF
# define FLOOR_COLOR 0x606060FF
# define WALL_NORTH_SOUTH 0x0000FFFF
# define WALL_EAST_WEST 0xFFFFFFFF
# define MOVESPEED 0.05
# define ROTSPEED 0.05

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
	int			map[5][5];
}				t_data;

typedef struct s_update_vars
{
    int			x, y;
    double		cx, rx, ry;
    int			mx, my;
    double		sdx, sdy;
    double		ddx, ddy;
    int			stepx, stepy;
    int			hit, side;
    double		pwd;
    int			lh, ds, de;
    uint32_t	col;
}				t_update_vars;

void			move_player(t_data *d, float mx, float my);
void			rotate(t_data *d, float rs);
void			key_hook(mlx_key_data_t kd, void *param);
void			update(void *param);

#endif