/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/29 10:53:40 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_gnl(remainder, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(remainder);
			remainder = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin_gnl(remainder, buffer);
	}
	if (!remainder)
		return (NULL);
	line = ft_strdup_gnl(remainder);
	temp = remainder;
	remainder = ft_strdup_gnl(ft_strchr_gnl(remainder, '\n') + 1);
	free(temp);
	return (line);
}
