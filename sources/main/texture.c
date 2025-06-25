/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:00:56 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/24 18:40:28 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	get_texture(t_data *d)
{
	d->t.north_texture = mlx_load_png("textures/bluestone.png");
	d->t.south_texture = mlx_load_png("textures/purplestone.png");
	d->t.east_texture = mlx_load_png("textures/pillar.png");
	d->t.west_texture = mlx_load_png("textures/wall_3.png");
	// d->t.north_texture = mlx_load_png(d->g->no);
	// d->t.south_texture = mlx_load_png(d->g->so);
	// d->t.east_texture = mlx_load_png(d->g->ea);
	// d->t.west_texture = mlx_load_png(d->g->we);
	if (!d->t.north_texture || !d->t.south_texture
		|| !d->t.east_texture || !d->t.west_texture)
	{
		printf("Error: Failed to load texture from the provided path");
		exit(1);
	}
}

void	calculate_texture_x(t_data *d, t_update_vars *v, mlx_texture_t *texture,
						double wall_x)
{
	d->t.tex_x = (int)(wall_x * texture->width);
	if (d->t.tex_x < 0)
		d->t.tex_x = 0;
	if (d->t.tex_x >= (int)texture->width)
		d->t.tex_x = texture->width - 1;
	if ((v->side == 2 || v->side == 3) && v->rx > 0)
		d->t.tex_x = texture->width - d->t.tex_x - 1;
	if ((v->side == 0 || v->side == 1) && v->ry < 0)
		d->t.tex_x = texture->width - d->t.tex_x - 1;
}

void	render_texture_pixel(t_data *d, mlx_texture_t *texture, int x, int y)
{
	int	pixel_index;

	pixel_index = (d->t.tex_y * texture->width + d->t.tex_x) * 4;
	d->t.r = texture->pixels[pixel_index + 0];
	d->t.g = texture->pixels[pixel_index + 1];
	d->t.b = texture->pixels[pixel_index + 2];
	d->t.a = texture->pixels[pixel_index + 3];
	d->t.color = (d->t.r << 24) | (d->t.g << 16) | (d->t.b << 8) | d->t.a;
	mlx_put_pixel(d->img, x, y, d->t.color);
}

void	render_texture_column(t_data *d, t_update_vars *v,
					mlx_texture_t *texture, int x)
{
	double	step;

	step = (double)texture->height / v->lh;
	d->t.tex_pos = (v->ds - HEIGHT / 2 + v->lh / 2) * step;
	v->y = v->ds;
	while (v->y <= v->de)
	{
		d->t.tex_y = (int)d->t.tex_pos;
		if (d->t.tex_y < 0)
			d->t.tex_y = 0;
		if (d->t.tex_y >= (int)texture->height)
			d->t.tex_y = texture->height - 1;
		render_texture_pixel(d, texture, x, v->y);
		d->t.tex_pos += step;
		v->y++;
	}
}

void	draw_textured_wall_strip(t_data *d, t_update_vars *v, int x)
{
	mlx_texture_t	*texture;
	double			wall_x;

	calculate_wall_boundaries(v);
	select_wall_texture(d, v, &texture);
	calculate_wall_x(d, v, &wall_x);
	calculate_texture_x(d, v, texture, wall_x);
	render_texture_column(d, v, texture, x);
}
