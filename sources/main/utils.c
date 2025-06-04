/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:01:04 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/04 00:01:06 by bszikora         ###   ########.fr       */
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
