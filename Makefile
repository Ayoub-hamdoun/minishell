# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:45:29 by ayhamdou          #+#    #+#              #
#    Updated: 2024/09/05 15:53:29 by ayhamdou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRCS = 
OBJS = $(SRCS:%.c=%.o)
MAIN = minishell.c

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

all : $(NAME)
	echo "COMPILED :)"

$(NAME) : $(HEADER) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(MAIN) -o $(NAME)

%.o : $(SRCS) $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

#todo : add object dir!!!