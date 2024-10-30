/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/30 01:50:01 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_read_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	temp_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while ((!buffer || !ft_strchr(buffer, '\n')) && bytes_read != 0)
	{
		buffer = ft_read_and_join(fd, buffer, temp_buffer);
		if (!buffer)
			break ;
	}
	free(temp_buffer);
	return (buffer);
}

static char	*ft_read_and_join(int fd, char *buffer, char *temp_buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(temp_buffer);
		free(buffer);
		return (NULL);
	}
	temp_buffer[bytes_read] = '\0';
	buffer = ft_strjoin(buffer, temp_buffer);
	return (buffer);
}

static char	*ft_update_buffer(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;
	size_t	buffer_len;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	buffer_len = ft_strlen(buffer);
	new_buffer = malloc((buffer_len - i + 1) * sizeof(char));
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
}
