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

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

static void	read_and_build_list(int fd, t_list **lst, int *bytes_read)
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
			break ;
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
