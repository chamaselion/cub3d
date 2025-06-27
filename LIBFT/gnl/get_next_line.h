/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:23:20 by bszikora          #+#    #+#             */
/*   Updated: 2025/05/27 18:41:23 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>  // for open
# include <stdio.h>  // for printf and perror
# include <stdlib.h> // for malloc, realloc, and frees
# include <string.h> // for strlen and strchr
# include <unistd.h> // for read and close

typedef struct s_gnl
{
	char	*buffer[2];
	char	*newline_pos;
	ssize_t	bytes_read;
	char	*line;
	char	*tmp;
	char	maybe;
}			t_gnl;

char		*ft_strchr(const char *s, int c);
ssize_t		ft_strl_gnl(const char *str);
char		*get_next_line(int fd);
void		*ft_memmove_gnl(void *dst, const void *src, ssize_t len);
char		*ft_strjoin_gnl(char *s1, char *s2);

#endif