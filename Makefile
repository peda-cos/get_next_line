# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 10:17:17 by peda-cos          #+#    #+#              #
#    Updated: 2024/10/28 10:40:17 by peda-cos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line
CC = cc
CFLAGS = -ggdb -Wall -Wextra -Werror -D BUFFER_SIZE=42
SRC = get_next_line.c get_next_line_utils.c main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
