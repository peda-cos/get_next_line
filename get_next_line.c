/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/30 02:54:02 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_alloc(char *alloc)
{
	int		i;
	int		j;
	char	*new_alloc;

	i = 0;
	while (alloc[i] && alloc[i] != '\n')
		i++;
	if (!alloc[i])
	{
		free(alloc);
		return (NULL);
	}
	new_alloc = (char *)malloc(sizeof(char) * (ft_strlen(alloc) - i + 1));
	if (!new_alloc)
		return (NULL);
	i++;
	j = 0;
	while (alloc[i])
		new_alloc[j++] = alloc[i++];
	new_alloc[j] = '\0';
	free(alloc);
	return (new_alloc);
}

static char	*extract_line(char *alloc)
{
	int		i;
	char	*line;

	i = 0;
	if (!alloc[i])
		return (NULL);
	while (alloc[i] && alloc[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (alloc[i] && alloc[i] != '\n')
	{
		line[i] = alloc[i];
		i++;
	}
	if (alloc[i] == '\n')
	{
		line[i] = alloc[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_and_alloc(int fd, char *alloc)
{
	ssize_t	read_bytes;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(alloc, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		alloc = ft_strjoin(alloc, buffer);
	}
	free(buffer);
	return (alloc);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*alloc;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	alloc = read_and_alloc(fd, alloc);
	if (!alloc)
		return (NULL);
	line = extract_line(alloc);
	alloc = update_alloc(alloc);
	return (line);
}
