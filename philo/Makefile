# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#              #
#    Updated: 2026/05/21 23:07:49 by kesaitou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -pthread

SRCS		:= main.c \
			   parse.c \
			   init.c \
			   init_mutex.c \
			   forks.c \
			   simulation.c \
			   routine.c \
			   monitor.c \
			   utils.c \
			   safe_pthread.c

OBJS		:= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re