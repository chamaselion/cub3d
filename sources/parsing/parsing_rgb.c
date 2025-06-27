/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:01:31 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/26 23:25:34 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgb_to_mlx_rgba(const int rgb[3])
{
	return (((uint32_t)rgb[0] << 24) | ((uint32_t)rgb[1] << 16)
		| ((uint32_t)rgb[2] << 8) | 255);
}

void	free_alloc(char **str)
{
	int	i;

	if (!str)
		return ;
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

void	check_rgb_num(char **c)
{
	int	count;

	count = 0;
	while (c[count])
		count++;
	if (count != 3)
		err_free_exit_msg("RGB must have exactly 3 numbers", c);
}

int	parse_rgb(const char *ln, int rgb[3])
{
	int		i;
	int		j;
	char	**c;
	char	*str;

	i = 0;
	while (ln[i] == ' ' || ft_isalpha(ln[i]))
		i++;
	c = ft_split(ln + i, ',');
	check_rgb_num(c);
	i = -1;
	while (c[++i])
	{
		str = c[i];
		while (*str == ' ' || *str == '\t')
			str++;
		j = 0;
		while (str[j] && str[j] != '\n' && str[j] != '\t' && str[j] != ' ')
			j++;
		str[j] = '\0';
		rgb[i] = ft_atoi(str);
		if (!is_pure_digit(str) || rgb[i] < 0 || rgb[i] > 255)
			err_free_exit_msg("Invalid RGB value", c);
	}
	return (free_alloc(c), 1);
}
