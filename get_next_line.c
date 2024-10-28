/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:11:09 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/28 11:33:37 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer, char *line, char **remainder)
{
	int		bytes_read;
	char	*newline_pos;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
		{
			*newline_pos = '\0';
			*remainder = ft_strdup(newline_pos + 1);
			line = ft_strjoin(line, buffer);
			return (line);
		}
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	if (remainder)
	{
		line = ft_strjoin(line, remainder);
		free(remainder);
		remainder = NULL;
		if (ft_strchr(line, '\n'))
			return (extract_line(&line, &remainder));
	}
	line = read_line(fd, buffer, line, &remainder);
	if (!line || (line[0] == '\0' && remainder == NULL))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
