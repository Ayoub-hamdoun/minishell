# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:45:29 by ayhamdou          #+#    #+#              #
#    Updated: 2024/12/21 00:43:18 by ayhamdou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = minishell.h

SRCS = utils/ft_split.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_substr.c\
		utils/ft_strtrim.c utils/ft_strjoin.c utils/ft_isalnum.c utils/ft_atoi.c utils/ft_strchr.c\
		utils/ft_putstr_fd.c utils/ft_itoa.c \
		parsing/parser.c parsing/tokenizer.c parsing/expander.c parsing/cleaner.c parsing/lexer.c\
		parsing/check_last_red.c parsing/env.c parsing/parser_helper_0.c parsing/quotes_handler.c\
		parsing/lexer_helper_0.c parsing/expander_helper_0.c parsing/tokenizer_helper_0.c\
		execution/builtins/the_echo.c execution/builtins/ft_exit.c execution/builtins/the_cd.c execution/builtins/the_export.c\
		execution/builtins/the_pwd.c execution/builtins/the_unset.c\
		execution/open_files.c execution/exec_commands.c execution/exec_commands_helper_0.c execution/open_files_helper_0.c\
		execution/open_files_helper_1.c execution/exec_commands_helper_1.c grbdg.c exit_status.c\
		minishell.c\
		parsing/tmp_file.c\

OBJS = $(SRCS:%.c=%.o)
MAIN = minishell.c

CC = cc
FLAGS = -Wall -Wextra -Werror -g
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