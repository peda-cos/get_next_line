/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/02 15:49:06 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_manager(char *temp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(temp) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (temp[i])
		str[j++] = temp[i++];
	str[j] = '\0';
	free(temp);
	return (str);
}

static char	*ft_next_line(char *temp)
{
	int		i;
	char	*str;

	i = 0;
	if (!temp[i])
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		str[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		str[i] = temp[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_read_temp(int fd, char *temp)
{
	ssize_t	reader;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	reader = 1;
	while (!ft_strchr(temp, '\n') && reader != 0)
	{
		reader = read(fd, buf, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[reader] = '\0';
		temp = ft_strjoin(temp, buf);
	}
	free(buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = ft_read_temp(fd, temp);
	if (!temp)
		return (NULL);
	line = ft_next_line(temp);
	temp = ft_manager(temp);
	return (line);
}
