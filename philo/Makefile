# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 10:53:49 by nelidris          #+#    #+#              #
#    Updated: 2022/03/28 15:37:10 by nelidris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAG = -Wall -Wextra -Werror

DEPS = deps/philosophers.c deps/utils.c deps/errors.c deps/routine.c deps/setup.c deps/time.c

NAME = philo

all: $(NAME)

$(NAME): $(DEPS)
	gcc $(CFLAG) -pthread $(DEPS) -o $(NAME) #-fsanitize=address

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

