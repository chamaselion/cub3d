/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:43:09 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/26 23:18:35 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(t_data *d, t_game *g)
{
	d->g = g;
	get_texture(d);
	init_player(d, d->g->player.x, d->g->player.y, get_spawn_angle(d->g->map));
	init_keys(d);
	d->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!d->mlx)
		return (ft_putstr_fd("Error: Failed to initialize MLX\n", 2),
			freexit(EXIT_FAILURE, d));
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img)
		return (ft_putstr_fd("Error: Failed to create image\n", 2),
			freexit(EXIT_FAILURE, d));
	if (mlx_image_to_window(d->mlx, d->img, 0, 0) < 0)
		return (ft_putstr_fd("Error: Failed to attach image to window\n", 2),
			freexit(EXIT_FAILURE, d));
	mlx_key_hook(d->mlx, key_hook, d);
	mlx_close_hook(d->mlx, (void (*)(void *))mlx_close_window, d->mlx);
	if (!mlx_loop_hook(d->mlx, update, d))
		return (ft_putstr_fd("Error: Failed to enter loop\n", 2),
			freexit(EXIT_FAILURE, d));
	mlx_loop(d->mlx);
	freexit(EXIT_SUCCESS, d);
}

int	init_game(t_game *g, char *argv1)
{
	g->height_map = 0;
	g->map = NULL;
	g->map_fd = -1;
	g->mlx = NULL;
	g->player = (t_player){0};
	g->width_map = 0;
	g->x = 0;
	g->y = 0;
	g->so = NULL;
	g->no = NULL;
	g->we = NULL;
	g->ea = NULL;
	g->c_rgba = 0xFFFFFFFF;
	g->f_rgba = 0xFFFFFFFF;
	read_map(g, argv1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;
	t_game	g;

	if (argc != 2)
		return (ft_putstr_fd("Bad arguments\n", 2), 1);
	init_data(&d);
	init_game(&g, argv[1]);
	validate_map(&g);
	start_game(&d, &g);
	return (EXIT_SUCCESS);
}
