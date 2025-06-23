/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_6_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:17:29 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/23 10:47:50 by aokhapki         ###   ########.fr       */
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
		printf("Processing line: %s\n", ln);
		*conf6 += parse_line(g, ln); // counting the variables we got
		printf("conf6: %d\n", *conf6);
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

int	parse_line(t_game *g, char *ln)
{
	int	n;

	n = 0;
	n += set_tex_path(&g->so, ln, "SO");
	n += set_tex_path(&g->we, ln, "WE");
	n += set_tex_path(&g->ea, ln, "EA");
	n += set_tex_path(&g->no, ln, "NO");
	// TODO for C and F
	return (n);
}
