/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:53:04 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/12 16:47:20 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static void read_and_build_list(int fd, t_list **lst, int *bytes_read)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	t_list	*new_node;

	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (*bytes_read > 0)
	{
		buffer[*bytes_read] = '\0';
		new_node = ft_lstnew(ft_strjoin("", buffer));
		if (*lst)
		{
			temp = ft_strjoin((*lst)->content, buffer);
			free((*lst)->content);
			(*lst)->content = temp;
		}
		else
		*lst = new_node;
		if (ft_strchr(buffer, '\n'))
			break;
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
}

static	char *ft_get_line(t_list *lst)
{
	size_t	len;
	char	*line;
	char	*temp;
	t_list	*temp_lst;

	len = 0;
	temp_lst = lst;
	while (temp_lst)
	{
		len += ft_strlen(temp_lst->content);
		temp_lst = temp_lst->next;
	}
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (lst)
	{
		temp = ft_strjoin(line, lst->content);
		free(line);
		line = temp;
		lst = lst->next;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char		*line;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_build_list(fd, &lst, &bytes_read);
	if (bytes_read < 0 || (!lst && bytes_read == 0))
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	line = ft_get_line(lst);
	ft_lstclear(&lst);
	return (line);
}
