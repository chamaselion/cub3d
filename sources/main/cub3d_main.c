/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:43:09 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/25 13:47:50 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_game(t_data *d, t_game *g)
{
	d->g = g;
	d->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(d->mlx, d->img, 0, 0);
	get_texture(d);
	init_player(d, 2, 2, get_spawn_angle(d->g->map));
	init_keys(d);
	mlx_key_hook(d->mlx, key_hook, d);
	mlx_close_hook(d->mlx, (void (*)(void *))mlx_close_window, d->mlx);
	mlx_loop_hook(d->mlx, update, d);
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
	mlx_delete_texture(d->t.north_texture);
	mlx_delete_texture(d->t.south_texture);
	mlx_delete_texture(d->t.east_texture);
	mlx_delete_texture(d->t.west_texture);
	free_char_array(d->g->map);
	return (0);
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

int	trim_it(t_game *g, t_data *d)
{
	int	c;

	c = 0;
	while (g->map[c])
		c++;
	d->g->map = malloc(sizeof(char *) * (c + 1));
	if (!d->g->map)
		return (1);
	d->g->map[c] = NULL;
	c = 0;
	while (g->map[c])
	{
		d->g->map[c] = trim_map_line(g->map[c]);
		c++;
	}
	free_char_array(g->map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;
	t_game	g;

	if (argc != 2)
		return (1);
	init_game(&g, argv[1]);
	// print the whole map delete after testing
	for (int i = 0; g.map[i]; i++)
		printf("line %d: %s", i, g.map[i]);
	printf("the path is: %s\n", g.no);
	printf("the path is: %s\n", g.we);
	printf("the path is: %s\n", g.so);
	printf("the path is: %s\n", g.ea);
	// print the colors
	printf("the color is: %d %d %d\n", g.c[0], g.c[1], g.c[2]);
	printf("the floor is: %d %d %d\n", g.f[0], g.f[1], g.f[2]);
	// validate_map(&g);
	// trim_it(&g, &d);
	start_game(&d, &g);
	return (EXIT_SUCCESS);
}
