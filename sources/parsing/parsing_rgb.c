/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:01:31 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/23 13:49:05 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgb_to_mlx_rgba(const int rgb[3])
{
    return ((uint32_t)rgb[0] << 24) | ((uint32_t)rgb[1] << 16) | ((uint32_t)rgb[2] << 8) | 255;
}

void	free_alloc(char **str)
{
    int	i;

    if (!str)
        return;
    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int	is_pure_digit(const char *str)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

//TODO make shorter till 25 lines
int	parse_rgb(const char *ln, int rgb[3])
{
	int		i = 0;
	char	**c;

	while (ln[i] == ' ' || ft_isalpha(ln[i]))
		i++;
	c = ft_split(ln + i, ',');
	i = 0;
	while (c[i] != NULL)
	{
		if (!is_pure_digit(c[i]))
		{
			printf("Error! RGB values must be numeric only\n");
			free_alloc(c);
			exit(EXIT_FAILURE);
		}
		rgb[i] = ft_atoi(c[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			printf("Error! Invalid RGB numbers\n");
			free_alloc(c);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free_alloc(c);
	return (1);
}
