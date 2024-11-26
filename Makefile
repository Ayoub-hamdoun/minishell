# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rallali <rallali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:45:29 by ayhamdou          #+#    #+#              #
#    Updated: 2024/11/26 00:31:23 by rallali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRCS = utils/ft_split.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_substr.c\
		utils/ft_strtrim.c utils/ft_strjoin.c utils/ft_isalnum.c parsing/env.c parsing/cleaner.c \
		parsing/parser.c parsing/tokenizer.c parsing/expander.c\
		parsing/lexer.c\

OBJS = $(SRCS:%.c=%.o)
MAIN = minishell.c

CC = cc
FLAGS = -Wall -Wextra -Werror 
RM = rm -rf

all : $(NAME)
	echo "COMPILED :)"

$(NAME) : $(HEADER) $(OBJS) $(MAIN)
	$(CC) $(FLAGS) $(OBJS) $(MAIN) -lreadline -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

#todo : add object dir!!!