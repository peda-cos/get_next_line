/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:11:09 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/29 03:36:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_load_line_from_buffer(char **line, char **buffers)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE && buffers[0][i])
	{
		if (buffers[0][i] == '\n')
		{
			*line = ft_strjoin(*line, buffers[0]);
			ft_memmove(buffers[0], buffers[0] + i + 1, BUFFER_SIZE - (i + 1));
			ft_memset(buffers[0] + BUFFER_SIZE - (i + 1), 0, i + 1);
			return (-1);
		}
		i++;
	}
	return (i);
}

static char	*ft_clear_buffer(char *line, char **buffers)
{
	if (buffers[0])
		free(buffers[0]);
	buffers[0] = NULL;
	return (line);
}

static char	*ft_read_line_fd(char *line, char **buffers, int fd)
{
	int	buffer_len;

	while (1)
	{
		buffer_len = ft_load_line_from_buffer(&line, buffers);
		if (buffer_len < 0)
			return (line);
		if (buffer_len > 0)
			line = ft_strjoin(line, buffers[0]);
		ft_memset(buffers[0], 0, BUFFER_SIZE);
		if (read(fd, buffers[0], BUFFER_SIZE) < 1)
			return (ft_clear_buffer(line, buffers));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffers[BUFFER_SIZE];

	if ((fd < 0) || (BUFFER_SIZE < 1))
		return (NULL);
	if (read(fd, NULL, 0) < 0)
		return (ft_clear_buffer(NULL, buffers + fd * (BUFFER_SIZE > 1)));
	if (buffers[fd * (BUFFER_SIZE > 1)] == NULL)
		buffers[fd * (BUFFER_SIZE > 1)] = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (buffers[fd * (BUFFER_SIZE > 1)] == NULL)
		return (NULL);
	return (ft_read_line_fd(NULL, buffers + fd * (BUFFER_SIZE > 1), fd));
}
