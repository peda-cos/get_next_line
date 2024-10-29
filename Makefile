# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 10:54:58 by peda-cos          #+#    #+#              #
#    Updated: 2024/10/29 10:55:53 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line

CC = cc
CFLAGS = -Wall -Wextra -Werror
BUFFER = -D BUFFER_SIZE=42

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(BUFFER) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
