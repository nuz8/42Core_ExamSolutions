# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 23:35:34 by pamatya           #+#    #+#              #
#    Updated: 2025/11/27 20:46:08 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	bsq
.DEFAULT_GOAL	:=	all
CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror

SRCS			:=	main.c bsq.c init.c parser.c utils.c

OBJS			:=	$(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
