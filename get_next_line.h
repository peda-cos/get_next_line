/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:04:45 by peda-cos          #+#    #+#             */
/*   Updated: 2024/10/29 02:53:32 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);

size_t  ft_strlen(const char *s);
void    *ft_memset(void *s, int c, size_t n);
void    *ft_memmove(void *dest, const void *src, size_t n);
void    *ft_calloc(size_t nmemb, size_t size);
char    *ft_strjoin(char const *s1, char const *s2);

#endif
