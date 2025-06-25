/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:09:09 by bszikora          #+#    #+#             */
/*   Updated: 2025/06/25 14:09:25 by bszikora         ###   ########.fr       */
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
