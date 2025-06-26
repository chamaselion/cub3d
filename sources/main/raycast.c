/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:00:53 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/26 15:33:51 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_direction(t_data *d, t_update_vars *v, int x)
{
	v->cx = 2 * x / (double)WIDTH - 1;
	v->rx = d->dx + d->plx * v->cx;
	v->ry = d->dy + d->ply * v->cx;
	v->mx = (int)d->px;
	v->my = (int)d->py;
	v->sdx = fabs(1 / v->rx);
	v->sdy = fabs(1 / v->ry);
}

void	setup_ray_steps(t_data *d, t_update_vars *v)
{
	if (v->rx < 0)
	{
		v->stepx = -1;
		v->ddx = (d->px - v->mx) * v->sdx;
	}
	else
	{
		v->stepx = 1;
		v->ddx = (v->mx + 1.0 - d->px) * v->sdx;
	}
	if (v->ry < 0)
	{
		v->stepy = -1;
		v->ddy = (d->py - v->my) * v->sdy;
	}
	else
	{
		v->stepy = 1;
		v->ddy = (v->my + 1.0 - d->py) * v->sdy;
	}
}

void	update_side(t_update_vars *v, int is_x)
{
	if (is_x)
	{
		v->ddx += v->sdx;
		v->mx += v->stepx;
		if (v->stepx < 0)
			v->side = 3;
		else
			v->side = 2;
	}
	else
	{
		v->ddy += v->sdy;
		v->my += v->stepy;
		if (v->stepy < 0)
			v->side = 0;
		else
			v->side = 1;
	}
}

void	perform_dda(t_data *d, t_update_vars *v)
{
	v->hit = 0;
	while (v->hit == 0)
	{
		if (v->ddx < v->ddy)
			update_side(v, 1);
		else
			update_side(v, 0);
		if (v->mx < 0 || v->my < 0 || v->mx >= d->g->width_map
			|| v->my >= d->g->height_map)
			break ;
		if (d->g->map[v->my][v->mx] == '1')
			v->hit = 1;
	}
}

void	cast_rays(t_data *d)
{
	t_update_vars	v;
	int				x;

	if (!d->t.north_texture)
		return ;
	x = 0;
	while (x < WIDTH)
	{
		calculate_ray_direction(d, &v, x);
		setup_ray_steps(d, &v);
		perform_dda(d, &v);
		calculate_wall_distance(d, &v);
		draw_textured_wall_strip(d, &v, x);
		x++;
	}
}
