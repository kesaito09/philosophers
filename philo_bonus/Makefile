NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
LDFLAGS = -pthread

SRCS = \
	entry_main.c \
	setup_parse.c \
	setup_init.c \
	setup_philo.c \
	setup_cleanup.c \
	parent_runtime.c \
	child_runtime.c \
	child_eat.c \
	child_routine.c \
	infra_semaphore.c \
	infra_time.c \
	infra_logger.c \
	infra_libs1.c \
	infra_libs2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
