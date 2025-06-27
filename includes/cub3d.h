/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:09:56 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/27 13:13:46 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MOVESPEED 0.05
# define ROTSPEED 0.05
# define EAST 0
# define NORTH 4.71238898038469 // Approximation of 3 * π / 2
# define WEST M_PI
# define SOUTH M_PI_2 

typedef struct s_keys
{
	bool			d;
	bool			s;
	bool			a;
	bool			w;
	bool			left;
	bool			right;
}					t_keys;

typedef struct s_textures
{
	mlx_texture_t	*south_texture;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_textures;

typedef struct s_update_vars
{
	int			x; // Current x coordinate for wall strip rendering
	int			y; // Current y coordinate for wall strip rendering
	double		cx; // Camera x coordinate (normalized screen x position)
	double		rx; // Ray direction X component
	double		ry; // Ray direction Y component
	int			mx; // Map X coordinate (current grid position)
	int			my; // Map Y coordinate (current grid position)
	double		sdx; // Step distance X (distance between X-side grid lines)
	double		sdy; // Step distance Y (distance between Y-side grid lines)
	double		ddx; // Delta distance X (accumulated distance to next X-side)
	double		ddy; // Delta distance Y (accumulated distance to next Y-side)
	int			stepx; // Step direction X (-1 or +1)
	int			stepy; // Step direction Y (-1 or +1)
	int			hit; // Hit flag (0 = no wall hit, 1 = wall hit)
	int			side; // Wall side hit: 0=NORTH, 1=SOUTH, 2=EAST, 3=WEST
	double		pwd; // Perpendicular wall distance (corrected for fisheye)
	int			lh; // Line height (wall slice height on screen)
	int			ds; // Draw start (top pixel of wall slice)
	int			de; // Draw end (bottom pixel of wall slice)
	uint32_t	col; // Color value for rendering
}				t_update_vars;

typedef struct s_player
{
	int				x;
	int				y;
}					t_player;

typedef struct s_game
{
	char			**map;
	char			*so;
	char			*no;
	char			*we;
	char			*ea;
	char			pos;
	int				c[3];
	int				f[3];
	int				map_fd;
	int				height_map;
	int				width_map;
	uint32_t		c_rgba;
	uint32_t		f_rgba;
	t_player		player;
}					t_game;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_game			*g;
	t_textures		t;
	float			px;
	float			dx;
	float			plx;
	float			py;
	float			dy;
	float			ply;
	t_keys			keys;
}					t_data;

void				move_player(t_data *d, float mx, float my);
void				rotate(t_data *d, float rs);
void				key_hook(mlx_key_data_t kd, void *param);
void				update(void *param);
void				init_player(t_data *d, int start_x, int start_y,
						float dir_angle);
void				handle_player_input(t_data *d);
void				draw_ceiling(mlx_image_t *img, uint32_t color);
void				draw_floor(mlx_image_t *img, uint32_t color);
void				calculate_ray_direction(t_data *d, t_update_vars *v, int x);
void				setup_ray_steps(t_data *d, t_update_vars *v);
void				perform_dda(t_data *d, t_update_vars *v);
void				calculate_wall_distance(t_data *d, t_update_vars *v);
void				cast_rays(t_data *d);
void				get_texture(t_data *d);
void				calculate_texture_x(t_data *d, t_update_vars *v,
						mlx_texture_t *texture, double wall_x);
void				render_texture_pixel(t_data *d, mlx_texture_t *texture,
						int x, int y);
void				render_texture_column(t_data *d, t_update_vars *v,
						mlx_texture_t *texture, int x);
void				draw_textured_wall_strip(t_data *d, t_update_vars *v,
						int x);
void				draw_wall_strip_paint(t_update_vars *v, t_data *d, int x);
void				draw_wall_strip(t_data *d, t_update_vars *v, int x);
void				calculate_wall_boundaries(t_update_vars *v);
void				select_wall_texture(t_data *d, t_update_vars *v,
						mlx_texture_t **texture);
void				calculate_wall_x(t_data *d, t_update_vars *v,
						double *wall_x);
void				free_char_array(char **array);
int					init_game(t_game *g, char *argv1);
void				start_game(t_data *d, t_game *g);
double				get_spawn_angle(char **map);
void				init_keys(t_data *d);
int					can_fit_on(char c);
char				*trim_texture_path(char *path);
void				freexit(int i, t_data *d);
void				init_data(t_data *d);
void				calculate_wall_distance(t_data *d, t_update_vars *v);

// char_validation
int					is_valid_char(char c);
int					is_wall(char c);
int					is_empty(char c);
int					is_player(char c);
void				normalize_spaces(t_game *game);
// map_validation
void				check_player_number(int nb);
void				find_player_pos(t_game *g);
void				validate_map(t_game *g);
// wall_validation
void				check_sides(t_game *g, int y, int x);
void				valid_walls(t_game *g, char **map, int y, int x);
// int					check_walls(t_game *game);
// parsing
int					whitespaces(char *str);
void				read_map(t_game *game, char *map);
void				fill_map(t_game *game, char *reader);
int					get_width_with_whitespaces(char *row);
void				find_width(t_game *game);
// parsing_6_lines.c
int					set_tex_path(char **tex_path, char *ln, char *prefix);
void				load_config(t_game *g);
void				process_line(t_game *g, char *ln, int *conf6);
void				verify_tex_dup(t_game *g);
int					parse_line(t_game *g, char *ln);
// parsing_rgb.c
uint32_t			rgb_to_mlx_rgba(const int rgb[3]);
int					parse_rgb(const char *ln, int rgb[3]);
void				check_rgb_num(char **c);
void				free_alloc(char **str);
// error_handling.c
void				err_exit_msg(char *msg);
void				err_free_exit_msg(char *msg, char **c);
#endif