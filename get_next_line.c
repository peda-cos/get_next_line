/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/12 07:45:37 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		i;

	ch = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (ch == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

static char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

static char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s) + 1;
	dup = (char *)malloc(sizeof(char) * len);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

static char	*get_line_from_list(t_list *lst)
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
	char			buffer[BUFFER_SIZE + 1];
	int				bytes_read;
	char			*newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(buffer)));
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0 || (!lst && bytes_read == 0))
		return (NULL);
	return (get_line_from_list(lst));
}
