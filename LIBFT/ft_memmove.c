/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alima <alima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:01:56 by aokhapki          #+#    #+#             */
/*   Updated: 2025/05/26 16:16:12 by alima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*source1;
	char		*dest1;

	dest1 = dst;
	source1 = src;
	if (dest1 < source1)
	{
		while (len > 0)
		{
			*dest1++ = *source1++;
			len--;
		}
	}
	else if (dest1 > source1)
	{
		dest1 += len;
		source1 += len;
		while (len > 0)
		{
			*(--dest1) = *(--source1);
			len--;
		}
	}
	return (dst);
}
