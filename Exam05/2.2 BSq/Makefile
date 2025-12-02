# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 23:35:34 by pamatya           #+#    #+#              #
#    Updated: 2025/12/02 15:45:47 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	bsq
.DEFAULT_GOAL	:=	all
CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror

SRCS			:=	bsq.c

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
