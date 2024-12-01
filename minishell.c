/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/01 17:41:27 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void l()
// {
// 	system("leaks minishell");
// }

void handle_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	// char *str = "     $HOME";
	// atexit(l);
	rl_catch_signals = 0;
	while(1)
	{
		signal(SIGINT, handle_sig);
		char *input = readline("GUMBALL$> ");
		if (!input)
			break;
		add_history(input);
		parser(input); 
	}
	// parser(str);
	return (0);
}
