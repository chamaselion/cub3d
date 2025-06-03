/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:43:09 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/03 18:42:03 by bszikora         ###   ########.fr       */
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

void	perform_dda(t_data *d, t_update_vars *v)
{
	v->hit = 0;
	while (v->hit == 0)
	{
		if (v->ddx < v->ddy)
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
		if (d->map[v->my][v->mx] == '1')
			v->hit = 1;
	}
}

void	calculate_wall_distance(t_data *d, t_update_vars *v)
{
	if (v->side == 2 || v->side == 3)
		v->pwd = (v->mx - d->px + (1 - v->stepx) / 2) / v->rx;
	else
		v->pwd = (v->my - d->py + (1 - v->stepy) / 2) / v->ry;
}

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

void	calculate_texture_coordinates(t_data *d, t_update_vars *v,
		double *wall_x, double *step)
{
	if (v->side == 2 || v->side == 3)
		*wall_x = d->py + v->pwd * v->ry;
	else
		*wall_x = d->px + v->pwd * v->rx;
	*wall_x = *wall_x - floor(*wall_x);
	d->t.tex_x = (int)(*wall_x * d->t.north_texture->width);
	if (d->t.tex_x < 0)
		d->t.tex_x = 0;
	if (d->t.tex_x >= (int)d->t.north_texture->width)
		d->t.tex_x = d->t.north_texture->width - 1;
	if ((v->side == 2 || v->side == 3) && v->rx > 0)
		d->t.tex_x = d->t.north_texture->width - d->t.tex_x - 1;
	if ((v->side == 0 || v->side == 1) && v->ry < 0)
		d->t.tex_x = d->t.north_texture->width - d->t.tex_x - 1;
	*step = (double)d->t.north_texture->height / v->lh;
	d->t.tex_pos = (v->ds - HEIGHT / 2 + v->lh / 2) * *step;
}

void	render_texture_column(t_data *d, t_update_vars *v, int x, double step)
{
	int	y;

	y = v->ds;
	while (y <= v->de)
	{
		d->t.tex_y = (int)d->t.tex_pos;
		if (d->t.tex_y < 0)
			d->t.tex_y = 0;
		if (d->t.tex_y >= (int)d->t.north_texture->height)
			d->t.tex_y = d->t.north_texture->height - 1;
		d->t.tex_pos += step;
		d->t.r = d->t.north_texture->pixels[(d->t.tex_y
				* d->t.north_texture->width + d->t.tex_x) * 4 + 0];
		d->t.g = d->t.north_texture->pixels[(d->t.tex_y
				* d->t.north_texture->width + d->t.tex_x) * 4 + 1];
		d->t.b = d->t.north_texture->pixels[(d->t.tex_y
				* d->t.north_texture->width + d->t.tex_x) * 4 + 2];
		d->t.a = d->t.north_texture->pixels[(d->t.tex_y
				* d->t.north_texture->width + d->t.tex_x) * 4 + 3];
		d->t.color = (d->t.r << 24) | (d->t.g << 16) | (d->t.b << 8) | d->t.a;
		mlx_put_pixel(d->img, x, y, d->t.color);
		y++;
	}
}

void	draw_textured_wall_strip(t_data *d, t_update_vars *v, int x)
{
	double	wall_x;
	double	step;

	v->lh = (int)(HEIGHT / v->pwd);
	v->ds = -v->lh / 2 + HEIGHT / 2;
	v->de = v->lh / 2 + HEIGHT / 2;
	if (v->ds < 0)
		v->ds = 0;
	if (v->de >= HEIGHT)
		v->de = HEIGHT - 1;
	calculate_texture_coordinates(d, v, &wall_x, &step);
	render_texture_column(d, v, x, step);
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

void	update(void *param)
{
	t_data	*d;

	d = param;
	handle_player_input(d);
	draw_ceiling(d->img);
	draw_floor(d->img);
	cast_rays(d);
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

int	init_game(t_game *g, char *argv1)
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

int	trim_it(t_game *g, t_data *d)
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

void	get_texture(t_data *d)
{
	d->t.north_texture = mlx_load_png("textures/bluestone.png");
	if (!d->t.north_texture)
	{
		printf("Error: Failed to load texture from textures/bluestone.png\n");
		exit(1);
	}
	printf("Texture loaded successfully: %dx%d, bytes_per_pixel: %d\n",
		d->t.north_texture->width, d->t.north_texture->height,
		d->t.north_texture->bytes_per_pixel);
}

int	start_game(t_data *d)
{
	d->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(d->mlx, d->img, 0, 0);
	get_texture(d);
	init_player(d, 1, 1.5, SOUTH);
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
	mlx_delete_texture(d->t.north_texture);
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