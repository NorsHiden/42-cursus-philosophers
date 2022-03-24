# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 10:53:49 by nelidris          #+#    #+#              #
#    Updated: 2022/03/24 16:32:42 by nelidris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAG = -Wall -Wextra -Werror

DEPS = deps/philosophers.c deps/utils.c

NAME = philo

all: $(NAME)

$(NAME): deps
	gcc $(CFLAG) -pthread $(DEPS) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

