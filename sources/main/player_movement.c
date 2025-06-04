/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:00:43 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/04 00:00:47 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *d, float mx, float my)
{
	if (d->map[(int)(d->py)][(int)(d->px + mx)] == '0')
		d->px += mx;
	if (d->map[(int)(d->py + my)][(int)(d->px)] == '0')
		d->py += my;
}

void	rotate(t_data *d, float rs)
{
	float	odx;
	float	oplx;

	odx = d->dx;
	d->dx = d->dx * cos(rs) - d->dy * sin(rs);
	d->dy = odx * sin(rs) + d->dy * cos(rs);
	oplx = d->plx;
	d->plx = d->plx * cos(rs) - d->ply * sin(rs);
	d->ply = oplx * sin(rs) + d->ply * cos(rs);
}

void	key_hook(mlx_key_data_t kd, void *param)
{
	t_data	*d;
	int		key;

	d = param;
	key = kd.key;
	if (key == MLX_KEY_W)
		d->keys.w = (kd.action != MLX_RELEASE);
	if (key == MLX_KEY_S)
		d->keys.s = (kd.action != MLX_RELEASE);
	if (key == MLX_KEY_A)
		d->keys.a = (kd.action != MLX_RELEASE);
	if (key == MLX_KEY_D)
		d->keys.d = (kd.action != MLX_RELEASE);
	if (key == MLX_KEY_LEFT)
		d->keys.left = (kd.action != MLX_RELEASE);
	if (key == MLX_KEY_RIGHT)
		d->keys.right = (kd.action != MLX_RELEASE);
	if (key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
		mlx_close_window(d->mlx);
}

void	init_player(t_data *d, float start_x, float start_y, float dir_angle)
{
	d->px = start_x;
	d->py = start_y;
	d->dx = cos(dir_angle);
	d->dy = sin(dir_angle);
	d->plx = -d->dy * 0.66;
	d->ply = d->dx * 0.66;
}

void	handle_player_input(t_data *d)
{
	if (d->keys.w)
		move_player(d, d->dx * MOVESPEED, d->dy * MOVESPEED);
	if (d->keys.s)
		move_player(d, -d->dx * MOVESPEED, -d->dy * MOVESPEED);
	if (d->keys.a)
		move_player(d, -d->plx * MOVESPEED, -d->ply * MOVESPEED);
	if (d->keys.d)
		move_player(d, d->plx * MOVESPEED, d->ply * MOVESPEED);
	if (d->keys.right)
		rotate(d, ROTSPEED);
	if (d->keys.left)
		rotate(d, -ROTSPEED);
}
