/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:45:27 by alima             #+#    #+#             */
/*   Updated: 2025/06/27 14:31:56 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	is_wall(char c)
{
	return (c == '1');
}

int	is_empty(char c)
{
	return (c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

int	is_player(char c)
{
	if (c != 'N' && c != 'E' && c != 'W' && c != 'S')
	{
		err_exit_msg("Wrong player character!");
		return (0);
	}
	return (1);
}
