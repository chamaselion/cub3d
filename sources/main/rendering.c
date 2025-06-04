/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:00:48 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/04 00:00:52 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(mlx_image_t *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, CEILING_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_floor(mlx_image_t *img)
{
	int	x;
	int	y;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, FLOOR_COLOR);
			x++;
		}
		y++;
	}
}

void	update(void *param)
{
	t_data	*d;

	d = param;
	handle_player_input(d);
	draw_ceiling(d->img);
	draw_floor(d->img);
	cast_rays(d);
}
