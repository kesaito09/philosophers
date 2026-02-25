NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -DPHILO_BONUS -Iinclude
LDFLAGS = -pthread

SRCS = \
	presentation/entry_main.c \
	presentation/setup_parse.c \
	presentation/setup_init.c \
	presentation/setup_philo.c \
	presentation/setup_cleanup.c \
	application/parent_runtime.c \
	application/child_runtime.c \
	domain/child_routine.c \
	domain/domain_philo_routine.c \
	domain/domain_philo_eat.c \
	infrastructure/infra_semaphore.c \
	infrastructure/infra_time.c \
	infrastructure/infra_logger.c \
	infrastructure/infra_libs1.c \
	infrastructure/infra_libs2.c \
	infrastructure/infra_ops.c \
	infrastructure/infra_ops_core.c \
	infrastructure/infra_ops_forks.c \
	infrastructure/infra_ops_sync.c

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
