/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42helbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:13:00 by bszikora          #+#    #+#             */
/*   Updated: 2025/05/27 18:41:24 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*ft_strndup(const char *s, ssize_t n)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	ft_memmove_gnl(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

int	initialize_buffer0(t_gnl *gnl)
{
	if (!gnl->buffer[0])
	{
		gnl->buffer[0] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!gnl->buffer[0])
			return (0);
		gnl->buffer[0][0] = '\0';
	}
	gnl->newline_pos = ft_strchr(gnl->buffer[0], '\n');
	gnl->bytes_read = 1;
	return (1);
}

int	process_buffer(t_gnl *gnl)
{
	free(gnl->buffer[1]);
	gnl->line = NULL;
	if (gnl->newline_pos != NULL)
	{
		gnl->line = ft_strndup(gnl->buffer[0], gnl->newline_pos - gnl->buffer[0]
				+ 1);
		if (!gnl->line)
			return (0);
		ft_memmove_gnl(gnl->buffer[0], gnl->newline_pos + 1,
			ft_strl_gnl(gnl->newline_pos + 1) + 1);
	}
	else if (ft_strl_gnl(gnl->buffer[0]) > 0)
	{
		gnl->line = ft_strndup(gnl->buffer[0], ft_strl_gnl(gnl->buffer[0]));
		if (!gnl->line)
			return (gnl->line = NULL, 0);
		*gnl->buffer[0] = '\0';
	}
	if (gnl->bytes_read <= 0)
	{
		free(gnl->buffer[0]);
		gnl->buffer[0] = NULL;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl;

	gnl.line = NULL;
	if (initialize_buffer0(&gnl) == 0)
		return (NULL);
	gnl.buffer[1] = malloc(BUFFER_SIZE + 1);
	while (gnl.newline_pos == NULL)
	{
		gnl.bytes_read = read(fd, gnl.buffer[1], BUFFER_SIZE);
		if (gnl.bytes_read <= 0)
			break ;
		gnl.buffer[1][gnl.bytes_read] = '\0';
		gnl.buffer[0] = ft_strjoin_gnl(gnl.buffer[0], gnl.buffer[1]);
		if (gnl.buffer[0] == NULL)
			return (free(gnl.buffer[1]), NULL);
		gnl.newline_pos = ft_strchr(gnl.buffer[0], '\n');
	}
	if (process_buffer(&gnl) == 0)
		return (free(gnl.buffer[0]), gnl.buffer[0] = NULL, NULL);
	if (gnl.bytes_read < 0)
		return (free(gnl.line), free(gnl.buffer[0]), NULL);
	return (gnl.line);
}

/*
int	main(void)
{
	char *line;
	int fd;

	fd = open("TEXT.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}*/