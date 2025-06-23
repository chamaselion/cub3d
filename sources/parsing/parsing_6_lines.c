/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_6_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:17:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/23 11:41:05 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_config(t_game *g)
{
	char	*ln;
	int		count;

	count = 0;
	ln = get_next_line(g->map_fd);
	while (ln != NULL)
	{
		process_line(g, ln, &count);
		free(ln);
		if (count == 6)
			break;
		ln = get_next_line(g->map_fd);
	}
	// verify_tex_dup(g);
	//load_tex(d);
}

void	process_line(t_game *g, char *ln, int *conf6)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ln[i] && !ft_isalpha(ln[i])) // skipping spaces, tabs and new lines until we find a letter
		i++;
	if (ln[i])
	{
		printf("Processing line: %s\n", ln); // debug print delete	
		*conf6 += parse_line(g, ln); // counting the variables we got
		printf("conf6: %d\n", *conf6); // debug print delete	
		if (*conf6 == 6)
			return;
	}
	// if the is no letter in this line, we have two cases:
	// 1. line is only spcases, or tabs or new lines: it is ok
	// 2. line has some random characters like # or $ , this is not ok, we give error message
	else
	{
		tmp = ln;
		while (*ln)
		{
			if (*tmp != '\n' && *tmp != ' ' && *tmp != '\t')
			{
				printf("Error\nInvalid config line!\n");
				exit(EXIT_FAILURE);
			}
			tmp++;
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
		{
			printf("Error\nDuplicate texture definition!\n");
			exit(EXIT_FAILURE);
		}
		*tex_path = ft_strdup(prefix_pos + (i + 2));
		return (1);
	}
	return (0);
}

int	parse_line(t_game *g, char *ln)
{
    int	n = 0;

    n += set_tex_path(&g->so, ln, "SO");
    n += set_tex_path(&g->we, ln, "WE");
    n += set_tex_path(&g->ea, ln, "EA");
    n += set_tex_path(&g->no, ln, "NO");

    if (ln[0] == 'C' && (ln[1] == ' ' || ln[1] == '\t'))
    {
        n += parse_rgb(ln, g->c);
        g->c_rgba = rgb_to_mlx_rgba(g->c);
    }
    else if (ln[0] == 'F' && (ln[1] == ' ' || ln[1] == '\t'))
    {
        n += parse_rgb(ln, g->f);
        g->f_rgba = rgb_to_mlx_rgba(g->f);
    }
    return (n);
}

void	verify_tex_dup(t_game *g)
{
	if (!g->so|| !g->no || !g->ea || !g->we)
	{
		printf("Error\nMissing texture path!\n");
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(g->so, g->no, ft_strlen(g->so)) == 0)
		|| (ft_strncmp(g->so, g->ea, ft_strlen(g->so)) == 0)
		|| (ft_strncmp(g->so, g->we, ft_strlen(g->so)) == 0))
	{
		printf("Error\nDuplicate texture detected!\n");
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(g->no, g->ea, ft_strlen(g->no)) == 0)
		|| (ft_strncmp(g->no, g->we, ft_strlen(g->no)) == 0))
	{
		printf("Error\nDuplicate texture detected!\n");
		exit(EXIT_FAILURE);
	}
	if ((ft_strncmp(g->ea, g->we, ft_strlen(g->ea)) == 0))
	{
		printf("Error\nDuplicate texture detected!\n");
		exit(EXIT_FAILURE);
	}
}
