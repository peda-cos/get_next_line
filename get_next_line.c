/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/12 16:09:20 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	while (s[len] != '\0')
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	*ptr = dest;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}

static	char *ft_get_line(t_list *lst)
{
	size_t	len;
	char	*line;
	t_list	*temp;

	len = 0;
	temp = lst;
	while (temp)
	{
		len += ft_strlen(temp->content);
		temp = temp->next;
	}
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (lst)
	{
		ft_strcat(line, lst->content);
		lst = lst->next;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char		buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char		*newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		ft_lstaddback(&lst, ft_lstnew(ft_strdup(buffer)));
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0 || (!lst && bytes_read == 0))
		return (NULL);
	return (ft_get_line(lst));
}
