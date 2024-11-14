/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/13 12:45:20 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buf, char *backup)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	if (!backup)
	{
		backup = ft_strdup("");
		if (!backup)
			return (NULL);
	}
	while (!ft_strchr(backup, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(backup);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		temp = backup;
		backup = ft_strjoin(temp, buf);
		free(temp);
		if (!backup)
			return (NULL);
	}
	return (backup);
}

static char	*get_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	line = ft_substr(backup, 0, i + 1);
	return (line);
}

static char	*new_backup(char *backup)
{
	int		i;
	char	*temp;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	temp = ft_substr(backup, i + 1, ft_strlen(backup) - i);
	free(backup);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	backup = read_line(fd, buf, backup);
	free(buf);
	if (!backup)
		return (NULL);
	line = get_line(backup);
	backup = new_backup(backup);
	return (line);
}
