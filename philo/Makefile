# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/17 20:39:44 by kesaitou          #+#    #+#              #
#    Updated: 2026/02/15 08:09:15 by kesaitou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
DEBUG ?= 0
CFLAGS = -Wall -Werror -Wextra -pthread
LDFLAGS = -pthread

ifeq ($(DEBUG),1)
	CFLAGS += -DDEBUG -g3 -O0
endif

MAND_SRCS = \
			philo_main.c\
			philo_parser.c\
			philo_setup.c\
			philo_sync.c\
			philo_forks.c\
			philo_simulation.c\
			philo_monitor.c\
			philo_routine.c\
			philo_logger.c\
			philo_utils.c\
			philo_time.c\
		


MAND_OBJS = $(MAND_SRCS:.c=.o)


all : $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME):$(MAND_OBJS) 
	$(CC) $(MAND_OBJS) $(LDFLAGS) -o $(NAME)
	
%.o : %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(MAND_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	$(MAKE) DEBUG=1 re


.PHONY: all clean fclean re debug
