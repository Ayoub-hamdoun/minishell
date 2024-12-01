# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:45:29 by ayhamdou          #+#    #+#              #
#    Updated: 2024/12/01 19:20:10 by ayhamdou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRCS = utils/ft_split.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_substr.c\
		utils/ft_strtrim.c utils/ft_strjoin.c utils/ft_isalnum.c\
		parsing/parser.c parsing/tokenizer.c parsing/expander.c parsing/cleaner.c parsing/lexer.c\
		parsing/check_last_red.c parsing/env.c\
		minishell.c

OBJS = $(SRCS:%.c=%.o)
MAIN = minishell.c

CC = cc
FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall -Wextra -Werror -fsanitize=address -g -O

I = -I/Users/ayhamdou/.brew/opt/readline/include
L = -L/Users/ayhamdou/.brew/opt/readline/lib

RM = rm -rf

all : $(NAME)
	echo "COMPILED :)"

$(NAME) : $(HEADER) $(OBJS) #$(MAIN)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME) $(L)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ $(I)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

#todo : add object dir!!!