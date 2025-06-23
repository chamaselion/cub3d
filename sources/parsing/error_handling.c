/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:09:43 by aokhapki          #+#    #+#             */
/*   Updated: 2025/06/23 13:44:37 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_exit_msg(const char *msg)
{
    printf("Error! %s\n", msg);
    exit(EXIT_FAILURE);
}
