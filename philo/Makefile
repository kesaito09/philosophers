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
			   init_mutex.c \
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

# valgrind tools are not available on macOS, so route through the Docker
# container (see ../docker/run.sh). On Linux you can still invoke valgrind
# directly with: valgrind --tool=helgrind ./philo $(ARGS)

helgrind:
	cd $(DOCKER_DIR) && ./run.sh helgrind $(ARGS)

drd:
	cd $(DOCKER_DIR) && ./run.sh drd $(ARGS)

memcheck:
	cd $(DOCKER_DIR) && ./run.sh memcheck $(ARGS)

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
