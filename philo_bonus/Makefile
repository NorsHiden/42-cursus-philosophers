# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 00:31:28 by nelidris          #+#    #+#              #
#    Updated: 2022/04/06 17:13:03 by nelidris         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAG = -Wall -Wextra -Werror

DEPS_BONUS = deps_bonus/philosophers_bonus.c deps_bonus/utils_bonus.c deps_bonus/errors_bonus.c deps_bonus/routine_bonus.c deps_bonus/setup_bonus.c deps_bonus/time_bonus.c

NAME = philo_bonus

all: $(NAME)

$(NAME): $(DEPS_BONUS)
	gcc $(CFLAG) -pthread $(DEPS_BONUS) -o $(NAME)

bonus: $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

