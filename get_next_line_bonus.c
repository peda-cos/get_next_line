/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/05 12:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	find_newline_position(const char *str)
{
	int	pos;

	pos = 0;
	while (str[pos] && str[pos] != '\n')
		pos++;
	return (pos);
}

static char	*read_until_newline(int fd, char *stash)
{
	char	*read_buffer;
	char	*new_stash;
	ssize_t	bytes_read;

	read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			free(stash);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		new_stash = ft_strjoin(stash, read_buffer);
		if (!new_stash)
			return (free(read_buffer), free(stash), NULL);
		stash = new_stash;
	}
	free(read_buffer);
	return (stash);
}

static char	*extract_line_from_stash(char *stash)
{
	char	*line;
	int		line_length;

	if (!stash || !stash[0])
		return (NULL);
	line_length = find_newline_position(stash);
	if (stash[line_length] == '\n')
		line_length++;
	line = ft_substr(stash, 0, line_length);
	return (line);
}

static char	*get_remaining_after_line(char *stash)
{
	char	*remaining;
	int		line_length;

	line_length = find_newline_position(stash);
	if (!stash[line_length])
	{
		free(stash);
		return (NULL);
	}
	line_length++;
	remaining = ft_strdup(stash + line_length);
	free(stash);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_until_newline(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line_from_stash(stash[fd]);
	stash[fd] = get_remaining_after_line(stash[fd]);
	return (line);
}
