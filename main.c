/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:36:19 by peda-cos          #+#    #+#             */
/*   Updated: 2024/11/14 16:37:20 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	char *line;
    int i = 1;

    while (i < argc)
    {
        fd = open(argv[i], O_RDONLY);
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s\n", line);
            free(line);
        }
        close(fd);
        i++;
    }
    return 0;
}
