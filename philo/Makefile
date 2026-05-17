# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/17 12:00:00 by kesaitou          #+#    #+#              #
#    Updated: 2026/05/17 17:11:00 by kesaitou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -pthread

SRCS		:= main.c \
			   parse.c \
			   init.c \
			   forks.c \
			   simulation.c \
			   routine.c \
			   monitor.c \
			   utils.c

OBJS		:= $(SRCS:.c=.o)

ARGS		?= 5 800 200 200 5

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

# ---------------------------------------------------------------------------- #
#  Docker (run from host)                                                      #
# ---------------------------------------------------------------------------- #

DOCKER_DIR	:= ../docker

docker-shell:
	cd $(DOCKER_DIR) && ./run.sh shell

docker-build:
	cd $(DOCKER_DIR) && docker compose build

docker-down:
	cd $(DOCKER_DIR) && ./run.sh down

# ---------------------------------------------------------------------------- #
#  Race / memory checks                                                        #
# ---------------------------------------------------------------------------- #

helgrind: $(NAME)
	valgrind --tool=helgrind \
	         --error-exitcode=42 \
	         --history-level=full \
	         ./$(NAME) $(ARGS)

drd: $(NAME)
	valgrind --tool=drd \
	         --error-exitcode=42 \
	         --exclusive-threshold=10000 \
	         --joinlist-threshold=10000 \
	         ./$(NAME) $(ARGS)

memcheck: $(NAME)
	valgrind --tool=memcheck \
	         --leak-check=full \
	         --show-leak-kinds=all \
	         --track-fds=yes \
	         --error-exitcode=42 \
	         ./$(NAME) $(ARGS)

TSAN_BIN	:= philo_tsan
TSAN_CC		:= clang
TSAN_CFLAGS	:= -Wall -Wextra -g -O1 -fsanitize=thread \
			   -fno-omit-frame-pointer -pthread

$(TSAN_BIN): $(SRCS) philo.h
	$(TSAN_CC) $(TSAN_CFLAGS) -o $@ $(SRCS)

tsan: $(TSAN_BIN)
	TSAN_OPTIONS='halt_on_error=1 second_deadlock_stack=1' \
	  ./$(TSAN_BIN) $(ARGS)

race: helgrind drd memcheck tsan
	@echo "--- all race checks passed ---"

tsan-clean:
	rm -f $(TSAN_BIN)

fclean: tsan-clean

.PHONY: all clean fclean re \
        docker-shell docker-build docker-down \
        helgrind drd memcheck tsan race tsan-clean
