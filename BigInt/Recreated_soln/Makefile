# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 23:35:34 by pamatya           #+#    #+#              #
#    Updated: 2025/11/05 20:02:44 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	BigInt
.DEFAULT_GOAL	:= all
CC				:=	c++
CFLAGS			:=	-Wall -Wextra -Werror -std=c++98

SRCS			:=	bigint.cpp main.cpp

OBJS			:=	$(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
