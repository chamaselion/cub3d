/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:01:00 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/04 16:23:57 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_strip_paint(t_update_vars *v, t_data *d, int x)
{
	v->y = v->ds;
	while (v->y <= v->de)
	{
		mlx_put_pixel(d->img, x, v->y, v->col);
		v->y++;
	}
}

void	draw_wall_strip(t_data *d, t_update_vars *v, int x)
{
	v->lh = (int)(HEIGHT / v->pwd);
	v->ds = -v->lh / 2 + HEIGHT / 2;
	v->de = v->lh / 2 + HEIGHT / 2;
	if (v->ds < 0)
		v->ds = 0;
	if (v->de >= HEIGHT)
		v->de = HEIGHT - 1;
	if (v->side == 1)
		v->col = WALL_SOUTH;
	if (v->side == 0)
		v->col = WALL_NORTH;
	if (v->side == 2)
		v->col = WALL_EAST;
	if (v->side == 3)
		v->col = WALL_WEST;
	draw_wall_strip_paint(v, d, x);
}

void	calculate_wall_boundaries(t_update_vars *v)
{
	v->lh = (int)(HEIGHT / v->pwd);
	v->ds = -v->lh / 2 + HEIGHT / 2;
	v->de = v->lh / 2 + HEIGHT / 2;
	if (v->ds < 0)
		v->ds = 0;
	if (v->de >= HEIGHT)
		v->de = HEIGHT - 1;
}

void	select_wall_texture(t_data *d, t_update_vars *v,
				mlx_texture_t **texture)
{
	if (v->side == 0)
		*texture = d->t.north_texture;
	else if (v->side == 1)
		*texture = d->t.south_texture;
	else if (v->side == 2)
		*texture = d->t.east_texture;
	else
		*texture = d->t.west_texture;
}

void	calculate_wall_x(t_data *d, t_update_vars *v, double *wall_x)
{
	if (v->side == 2 || v->side == 3)
		*wall_x = d->py + v->pwd * v->ry;
	else
		*wall_x = d->px + v->pwd * v->rx;
	*wall_x = *wall_x - floor(*wall_x);
}
