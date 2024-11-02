/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/02 15:38:03 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*allocator(char *alloc)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (alloc[i] && alloc[i] != '\n')
		i++;
	if (!alloc[i])
	{
		free(alloc);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(alloc) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (alloc[i])
		str[j++] = alloc[i++];
	str[j] = '\0';
	free(alloc);
	return (str);
}

static char	*next_line(char *alloc)
{
	int		i;
	char	*str;

	i = 0;
	if (!alloc[i])
		return (NULL);
	while (alloc[i] && alloc[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (alloc[i] && alloc[i] != '\n')
	{
		str[i] = alloc[i];
		i++;
	}
	if (alloc[i] == '\n')
	{
		str[i] = alloc[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*read_alloc(int fd, char *alloc)
{
	ssize_t	reader;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	reader = 1;
	while (!ft_strchr(alloc, '\n') && reader != 0)
	{
		reader = read(fd, buf, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[reader] = '\0';
		alloc = ft_strjoin(alloc, buf);
	}
	free(buf);
	return (alloc);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*alloc;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	alloc = read_alloc(fd, alloc);
	if (!alloc)
		return (NULL);
	line = next_line(alloc);
	alloc = allocator(alloc);
	return (line);
}
