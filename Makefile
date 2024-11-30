# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rallali <rallali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:45:29 by ayhamdou          #+#    #+#              #
#    Updated: 2024/11/30 21:12:09 by rallali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRCS = utils/ft_split.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_substr.c\
		utils/ft_strtrim.c utils/ft_strjoin.c utils/ft_isalnum.c\
		parsing/parser.c parsing/tokenizer.c parsing/expander.c parsing/cleaner.c parsing/lexer.c\
		parsing/check_last_red.c\

OBJS = $(SRCS:%.c=%.o)
MAIN = minishell.c

CC = cc
# FLAGS = -Wall -Wextra -Werror
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g -O

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