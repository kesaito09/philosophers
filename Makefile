# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/17 20:39:44 by kesaitou          #+#    #+#              #
#    Updated: 2026/01/17 21:01:37 by kesaitou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra

MAND_SRCS = srcs/philo.c\


MAND_OBJS = $(MAND_SRCS:.c=.o)


all : $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(NAME):$(MAND_OBJS) $(LIBFT)
	$(CC) $(MAND_OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	
%.o : %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(MAND_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all


.PHONY: all clean fclean re