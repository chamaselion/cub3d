/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:01:31 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/23 11:29:54 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	rgb_to_mlx_rgba(const int rgb[3])
{
    return ((uint32_t)rgb[0] << 24) | ((uint32_t)rgb[1] << 16) | ((uint32_t)rgb[2] << 8) | 255;
}

int	parse_rgb(const char *ln, int *rgb)
{
    const char *ptr = ln;

    while (*ptr && !(*ptr >= '0' && *ptr <= '9'))
        ptr++;
    rgb[0] = ft_atoi(ptr);
    while (*ptr && *ptr != ',')
        ptr++;
    if (*ptr != ',')
    {
        printf("Error\nInvalid RGB format!\n");
        exit(EXIT_FAILURE);
    }
    ptr++;
    rgb[1] = ft_atoi(ptr);
    while (*ptr && *ptr != ',')
        ptr++;
    if (*ptr != ',')
    {
        printf("Error\nInvalid RGB format!\n");
        exit(EXIT_FAILURE);
    }
    ptr++;
    rgb[2] = ft_atoi(ptr);

    if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
    {
        printf("Error\nRGB values out of range!\n");
        exit(EXIT_FAILURE);
    }
    return (1);
}
