/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:09:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/24 22:17:28 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_exit_msg(const char *msg)
{
    printf("Error! %s\n", msg);
    exit(EXIT_FAILURE);
}
void	err_free_exit_msg(const char *msg, char **c)
{
    printf("Error! %s\n", msg);
    free_alloc(c);
    exit(EXIT_FAILURE);
}