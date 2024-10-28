/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:11:09 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/28 11:47:38 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **line, char **remainder)
{
	char	*newline_pos;
	char	*temp;
	size_t	len;

	newline_pos = ft_strchr(*line, '\n');
	if (newline_pos)
	{
		len = newline_pos - *line + 1;
		temp = ft_substr(*line, 0, len);
		*remainder = ft_strdup(newline_pos + 1);
		free(*line);
		*line = NULL;
		return (temp);
	}
	return (*line);
}

static char	*read_line(int fd, char *buffer, char *line, char **remainder)
{
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(line, buffer);
		free(line);
		if (!temp)
			return (NULL);
		line = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(line);
		return (NULL);
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
	if (!line)
		return (NULL);
	if (remainder)
	{
		line = ft_strjoin(line, remainder);
		free(remainder);
		remainder = NULL;
		if (ft_strchr(line, '\n'))
			return (extract_line(&line, &remainder));
	}
	line = read_line(fd, buffer, line, &remainder);
	if (!line)
		return (NULL);
	return (extract_line(&line, &remainder));
}
