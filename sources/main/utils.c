/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:01:04 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/24 19:04:26 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	can_fit_on(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '0')
		return (1);
	return (0);
}

void	init_keys(t_data *d)
{
	d->keys.w = false;
	d->keys.s = false;
	d->keys.a = false;
	d->keys.d = false;
	d->keys.left = false;
	d->keys.right = false;
}

double	get_spawn_angle(char **map)
{
	int		i;
	int		j;
	char	c;

	if (map == NULL)
		return (-1);
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j++] != '\0')
		{
			c = map[i][j];
			if (c == 'N')
				return (NORTH);
			if (c == 'S')
				return (SOUTH);
			if (c == 'E')
				return (EAST);
			if (c == 'W')
				return (WEST);
		}
		i++;
	}
	return (-1);
}
