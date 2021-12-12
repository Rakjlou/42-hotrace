# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 23:54:46 by nsierra-          #+#    #+#              #
#    Updated: 2021/12/12 06:46:38 by nsierra-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = hotrace

SRC = get_next_line.c \
	get_next_line_utils.c \
	utils.c \
	utils2.c \
	avl_utils.c \
	avl_insert.c \
	avl_rotate.c \
	avl_find.c \
	main.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
