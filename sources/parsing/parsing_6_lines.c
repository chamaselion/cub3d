/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_6_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:17:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/27 11:55:47 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_config(t_game *g)
{
	char	*ln;
	int		count;

	count = 0;
	ln = get_next_line(g->map_fd);
	if (!ln)
		err_exit_msg("Error reading from file");
	while (ln != NULL)
	{
		process_line(g, ln, &count);
		free(ln);
		if (count == 6)
			break ;
		ln = get_next_line(g->map_fd);
	}
}

void	process_line(t_game *g, char *ln, int *conf6)
{
	int	i;

	i = 0;
	while (ln[i] && !ft_isalpha(ln[i]))
		i++;
	if (ln[i])
	{
		*conf6 += parse_line(g, ln);
		if (*conf6 == 6)
			return ;
	}
	else
	{
		while (*ln)
		{
			if (*ln != '\n' && *ln != ' ' && *ln != '\t')
				err_exit_msg("Invalid line in config file!");
			ln++;
		}
	}
}

// prefix = SO, NO etc
int	set_tex_path(char **tex_path, char *ln, char *prefix)
{
	int		i;
	char	*prefix_pos;

	i = 0;
	prefix_pos = ft_strnstr(ln, prefix, ft_strlen(ln));
	if (prefix_pos != NULL)
	{
		while (prefix_pos[i + 2] == ' ' || prefix_pos[i + 2] == '\t')
			i++;
		if (*tex_path != NULL)
			err_exit_msg("Duplicate texture definition!");
		*tex_path = ft_strdup(prefix_pos + (i + 2));
		return (1);
	}
	return (0);
}

int	parse_line(t_game *g, char *ln)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	n += set_tex_path(&g->so, ln, "SO");
	n += set_tex_path(&g->we, ln, "WE");
	n += set_tex_path(&g->ea, ln, "EA");
	n += set_tex_path(&g->no, ln, "NO");
	while (ln[i] == ' ' || ln[i] == '\t')
		i++;
	if (ln[i] == 'C' && (ln[i + 1] == ' ' || ln[i + 1] == '\t'))
	{
		n += parse_rgb(ln + i, g->c);
		g->c_rgba = rgb_to_mlx_rgba(g->c);
	}
	else if (ln[i] == 'F' && (ln[i + 1] == ' ' || ln[i + 1] == '\t'))
	{
		n += parse_rgb(ln + i, g->f);
		g->f_rgba = rgb_to_mlx_rgba(g->f);
	}
	return (n);
}

void	verify_tex_dup(t_game *g)
{
	if (!g->so || !g->no || !g->ea || !g->we)
		err_exit_msg("Missing texture path!");
	if ((ft_strncmp(g->so, g->no, ft_strlen(g->so)) == 0) || (ft_strncmp(g->so,
				g->ea, ft_strlen(g->so)) == 0) || (ft_strncmp(g->so, g->we,
				ft_strlen(g->so)) == 0))
		err_exit_msg("Duplicate texture detected!");
	if ((ft_strncmp(g->no, g->ea, ft_strlen(g->no)) == 0) || (ft_strncmp(g->no,
				g->we, ft_strlen(g->no)) == 0))
		err_exit_msg("Duplicate texture detected!");
	if ((ft_strncmp(g->ea, g->we, ft_strlen(g->ea)) == 0))
		err_exit_msg("Duplicate texture detected!");
}
