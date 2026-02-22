# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/17 20:39:44 by kesaitou          #+#    #+#              #
#    Updated: 2026/02/22 20:58:05 by kesaitou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
LDFLAGS = -pthread


SRCS = \
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
		


OBJS = $(SRCS:.c=.o)


all : $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME):$(OBJS) 
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	
%.o : %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
