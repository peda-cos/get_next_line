/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/05 12:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	if (!str)
		return (0);
	while (str[length])
		length++;
	return (length);
}

char	*ft_strchr(const char *str, int target)
{
	int		index;
	char	target_char;

	index = 0;
	target_char = (char)target;
	if (!str)
		return (NULL);
	while (str[index])
	{
		if (str[index] == target_char)
			return ((char *)(str + index));
		index++;
	}
	if (target_char == '\0')
		return ((char *)(str + index));
	return (NULL);
}

char	*ft_strdup(const char *source)
{
	char	*duplicate;
	int		index;
	int		length;

	if (!source)
		return (NULL);
	length = ft_strlen(source);
	duplicate = malloc(sizeof(char) * (length + 1));
	if (!duplicate)
		return (NULL);
	index = 0;
	while (source[index])
	{
		duplicate[index] = source[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate);
}

char	*ft_strjoin(char *prefix, char *suffix)
{
	char	*result;
	int		total_length;
	int		pos;
	int		idx;

	if (!prefix && !suffix)
		return (NULL);
	total_length = ft_strlen(prefix) + ft_strlen(suffix);
	result = malloc(sizeof(char) * (total_length + 1));
	if (!result)
		return (NULL);
	pos = 0;
	idx = 0;
	while (prefix && prefix[idx])
		result[pos++] = prefix[idx++];
	idx = 0;
	while (suffix && suffix[idx])
		result[pos++] = suffix[idx++];
	result[pos] = '\0';
	if (prefix)
		free(prefix);
	return (result);
}

char	*ft_substr(char const *source, unsigned int start, size_t max_length)
{
	char	*substring;
	size_t	index;
	size_t	source_length;

	if (!source)
		return (NULL);
	source_length = ft_strlen(source);
	if (start >= source_length)
		return (ft_strdup(""));
	if (max_length > source_length - start)
		max_length = source_length - start;
	substring = malloc(sizeof(char) * (max_length + 1));
	if (!substring)
		return (NULL);
	index = 0;
	while (index < max_length && source[start + index])
	{
		substring[index] = source[start + index];
		index++;
	}
	substring[index] = '\0';
	return (substring);
}
