/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:09:09 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/26 11:24:24 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*trim_texture_path(char *path)
{
	int		len;
	char	*trimmed;

	if (!path)
		return (NULL);
	trimmed = ft_strdup(path);
	if (!trimmed)
		return (NULL);
	len = ft_strlen(trimmed);
	while (len > 0 && (trimmed[len - 1] == '\n' || trimmed[len - 1] == ' '
			|| trimmed[len - 1] == '\t' || trimmed[len - 1] == '\r'))
	{
		trimmed[len - 1] = '\0';
		len--;
	}
	return (trimmed);
}

void	freexit(int i, t_data *d)
{
	t_game	*g;

	g = NULL;
	if (d)
	{
		g = d->g;
		if (g)
		{
			if (g->map)
				free_char_array(g->map);
			if (g->no)
				free(g->no);
			if (g->so)
				free(g->so);
			if (g->we)
				free(g->we);
			if (g->ea)
				free(g->ea);
			if (g->map_fd >= 0)
				close(g->map_fd);
		}
		if (d->t.north_texture)
			mlx_delete_texture(d->t.north_texture);
		if (d->t.south_texture)
			mlx_delete_texture(d->t.south_texture);
		if (d->t.east_texture)
			mlx_delete_texture(d->t.east_texture);
		if (d->t.west_texture)
			mlx_delete_texture(d->t.west_texture);
		if (d->mlx)
			mlx_terminate(d->mlx);
	}
	exit(i);
}

void	init_data(t_data *d)
{
	if (!d)
		return ;
	d->mlx = NULL;
	d->img = NULL;
	d->g = NULL;
	d->t.north_texture = NULL;
	d->t.south_texture = NULL;
	d->t.east_texture = NULL;
	d->t.west_texture = NULL;
	d->t.tex_pos = 0.0;
	d->t.tex_x = 0;
	d->t.tex_y = 0;
	d->t.r = 0;
	d->t.g = 0;
	d->t.b = 0;
	d->t.a = 0;
	d->t.color = 0;
	d->px = 0.0;
	d->dx = 0.0;
	d->plx = 0.0;
	d->py = 0.0;
	d->dy = 0.0;
	d->ply = 0.0;
	init_keys(d);
}
