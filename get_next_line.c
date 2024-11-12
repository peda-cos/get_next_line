/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/12 07:10:09 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*string_char(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

static size_t	get_line_length(t_list *lst)
{
	size_t	len;
	char	*newline_pos;

	len = 0;
	while (lst)
	{
		newline_pos = string_char(lst->content, '\n');
		if (newline_pos)
		{
			len += (newline_pos - lst->content + 1);
			break ;
		}
		len += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (len);
}

static void	copy_line_content(char *line, t_list *lst, size_t len)
{
	size_t	i;
	char	*newline_pos;

	i = 0;
	while (lst && len)
	{
		newline_pos = string_char(lst->content, '\n');
		if (newline_pos)
		{
			while (lst->content && lst->content != newline_pos + 1)
				*line++ = *lst->content++;
			*line = '\0';
			return ;
		}
		while (*lst->content)
			*line++ = *lst->content++;
		lst = lst->next;
	}
	*line = '\0';
}

static char	*extract_line(t_list **lst)
{
	char	*line;
	size_t	len;

	if (!*lst)
		return (NULL);
	len = get_line_length(*lst);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	copy_line_content(line, *lst, len);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*new_node;
	char			buffer[BUFFER_SIZE + 1];
	char			*newline_pos;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		new_node = ft_lstnew(ft_strdup(buffer));
		if (!new_node)
		{
			ft_lstdel(&lst);
			return (NULL);
		}
		ft_lstadd_back(&lst, new_node);
		newline_pos = string_char(buffer, '\n');
		if (newline_pos)
			break ;
	}
	if (bytes_read < 0 || (!lst && bytes_read == 0))
	{
		ft_lstdel(&lst);
		return (NULL);
	}
	return (extract_line(&lst));
}
