/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:43:09 by bszikora          #+#    #+#             */
/*   Updated: 2025/05/30 09:35:23 by bszikora         ###   ########.fr       */
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

void	update(void *param)
{
	t_data			*d;
	t_update_vars	v;

	d = param;
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
	v.y = 0;
	while (v.y < HEIGHT / 2)
	{
		v.x = 0;
		while (v.x < WIDTH)
		{
			mlx_put_pixel(d->img, v.x, v.y, CEILING_COLOR);
			v.x++;
		}
		v.y++;
	}
	v.y = HEIGHT / 2;
	while (v.y < HEIGHT)
	{
		v.x = 0;
		while (v.x < WIDTH)
		{
			mlx_put_pixel(d->img, v.x, v.y, FLOOR_COLOR);
			v.x++;
		}
		v.y++;
	}
	v.x = 0;
	while (v.x < WIDTH)
	{
		v.cx = 2 * v.x / (double)WIDTH - 1;
		v.rx = d->dx + d->plx * v.cx;
		v.ry = d->dy + d->ply * v.cx;
		v.mx = (int)d->px;
		v.my = (int)d->py;
		v.sdx = fabs(1 / v.rx);
		v.sdy = fabs(1 / v.ry);
		if (v.rx < 0)
			v.stepx = -1;
		else
			v.stepx = 1;
		if (v.rx < 0)
			v.ddx = (d->px - v.mx) * v.sdx;
		else
			v.ddx = (v.mx + 1.0 - d->px) * v.sdx;
		if (v.ry < 0)
			v.stepy = -1;
		else
			v.stepy = 1;
		if (v.ry < 0)
			v.ddy = (d->py - v.my) * v.sdy;
		else
			v.ddy = (v.my + 1.0 - d->py) * v.sdy;
		v.hit = 0;
		while (!v.hit)
		{
			if (v.ddx < v.ddy)
			{
				v.ddx += v.sdx;
				v.mx += v.stepx;
				v.side = 0;
			}
			else
			{
				v.ddy += v.sdy;
				v.my += v.stepy;
				v.side = 1;
			}
			if (d->map[v.my][v.mx] == '1')
				v.hit = 1;
		}
		if (v.side)
			v.pwd = (v.my - d->py + (1 - v.stepy) / 2) / v.ry;
		else
			v.pwd = (v.mx - d->px + (1 - v.stepx) / 2) / v.rx;
		v.lh = (int)(HEIGHT / v.pwd);
		v.ds = -v.lh / 2 + HEIGHT / 2;
		v.de = v.lh / 2 + HEIGHT / 2;
		if (v.ds < 0)
			v.ds = 0;
		if (v.de >= HEIGHT)
			v.de = HEIGHT - 1;
		if (v.side)
			v.col = WALL_EAST_WEST;
		else
			v.col = WALL_NORTH_SOUTH;
		v.y = v.ds;
		while (v.y <= v.de)
		{
			mlx_put_pixel(d->img, v.x, v.y, v.col);
			v.y++;
		}
		v.x++;
	}
	//usleep(16666);
}

char	*trim_map_line(char *line)
{
	int		i;
	int		j;
	char	*trimmed;

	if (!line)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			trimmed[j++] = line[i];
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int init_game(t_game *g, char *argv1)
{
	g->height_map = 0;
	g->map = NULL;
	g->map_fd = -1;
	g->mlx = NULL;
	g->player = (t_player){0};
	g->width_map = 0;
	g->x = 0;
	g->x = 0;
	read_map(g, argv1);
	return (0);
}

int trim_it(t_game *g, t_data *d)
{
	int	c;

	c = 0;
	while (g->map[c])
		c++;
	d->map = malloc(sizeof(char *) * (c + 1));
	if (!d->map)
		return (1);
	d->map[c] = NULL;
	c = 0;
	while (g->map[c])
	{
		d->map[c] = trim_map_line(g->map[c]);
		c++;
	}
	free_char_array(g->map);
	return (0);
}

int start_game(t_data *d)
{
	d->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(d->mlx, d->img, 0, 0);
	init_player(d, 1, 1.5, NORTH);
	d->keys.w = false;
	d->keys.s = false;
	d->keys.a = false;
	d->keys.d = false;
	d->keys.left = false;
	d->keys.right = false;
	mlx_key_hook(d->mlx, key_hook, d);
	mlx_close_hook(d->mlx, (void (*)(void *))mlx_close_window, d->mlx);
	mlx_loop_hook(d->mlx, update, d);
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
	free_char_array(d->map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;
	t_game	g;

	if (argc != 2)
		return (1);
	init_game(&g, argv[1]);
	trim_it(&g, &d);
	start_game(&d);
	return (EXIT_SUCCESS);
}

	// char **cc = d.map;
	// int ii = 0;
	// if (cc)
	// {
	// 	while (cc[ii])
	// 	{
	// 		printf("line: %s\n", cc[ii]);
	// 		ii++;
	// 	}
	// }