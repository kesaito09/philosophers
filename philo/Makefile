NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -Iinclude
LDFLAGS = -pthread

SRCS = \
	presentation/philo_main.c \
	presentation/philo_parser.c \
	presentation/philo_setup.c \
	presentation/philo_cleanup.c \
	application/philo_simulation.c \
	application/philo_monitor.c \
	domain/philo_routine.c \
	domain/domain_philo_routine.c \
	domain/domain_philo_eat.c \
	infrastructure/philo_sync.c \
	infrastructure/philo_logger.c \
	infrastructure/philo_utils.c \
	infrastructure/philo_time.c \
	infrastructure/philo_ops.c \
	infrastructure/philo_ops_core.c \
	infrastructure/philo_ops_forks.c \
	infrastructure/philo_ops_sync.c \
	infrastructure/philo_resource.c \
	infrastructure/philo_resource_locks.c

OBJS = $(SRCS:.c=.o)
HEADERS = \
	include/philo_app.h \
	include/philo_domain.h \
	include/philo_infra.h \
	include/philo_presentation.h \
	include/philo_types.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
