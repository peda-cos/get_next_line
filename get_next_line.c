/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/12 07:38:47 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_fd_node(t_list **lst, int fd)
{
	t_list	*temp;
	t_list	*new_node;
	char	*buffer;

	temp = *lst;
	while (temp)
	{
		if (*(int *)(temp->content) == fd)
			return (temp);
		temp = temp->next;
	}
	buffer = (char *)malloc(sizeof(int) + 1);
	if (!buffer)
		return (NULL);
	*(int *)buffer = fd;
	new_node = ft_lstnew(buffer);
	if (!new_node)
	{
		free(buffer);
		return (NULL);
	}
	ft_lstadd_back(lst, new_node);
	return (new_node);
}

static char	*extract_line(t_list **lst, t_list *fd_node)
{
	char	*line;
	size_t	len;
	t_list	*temp;
	t_list	*prev;
	char	*newline_pos;

	len = 0;
	line = NULL;
	temp = fd_node->next;
	prev = fd_node;
	while (temp)
	{
		newline_pos = ft_strchr(temp->content, '\n');
		if (newline_pos)
		{
			len += newline_pos - temp->content + 1;
			line = (char *)malloc(len + 1);
			if (!line)
				return (NULL);
			line[0] = '\0';
			temp = fd_node->next;
			while (temp && temp != temp->next)
			{
				ft_strcat(line, temp->content);
				if (ft_strchr(temp->content, '\n'))
					break ;
				temp = temp->next;
			}
			return (line);
		}
		len += ft_strlen(temp->content);
		temp = temp->next;
	}
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	temp = fd_node->next;
	while (temp)
	{
		ft_strcat(line, temp->content);
		temp = temp->next;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*fd_node;
	char			buffer[BUFFER_SIZE + 1];
	int				bytes_read;
	char			*newline_pos;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = get_fd_node(&lst, fd);
	if (!fd_node)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		ft_lstadd_back(&fd_node->next, ft_lstnew(ft_strdup(buffer)));
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0 || (!fd_node->next && bytes_read == 0))
		return (NULL);
	line = extract_line(&lst, fd_node);
	return (line);
}
