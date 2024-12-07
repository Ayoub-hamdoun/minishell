/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/07 19:49:24 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	t_env *ev;
	// t_command *commands = NULL;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		write(2, "not a tty!\n", 12);
		return (0);
	}
	ev = malloc (sizeof(t_env));
	// atexit(l);
	rl_catch_signals = 0;
	dup_env(ev, env);
	while(1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		char *input = readline("GUMBALL$> ");
		if (!input)
			break ;
		add_history(input);
		// do_all(input,ev);
		parser(input, ev, env);

		// exec();
	}
	return (0);
}
