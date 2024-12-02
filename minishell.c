/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/02 14:03:41 by ayhamdou         ###   ########.fr       */
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
void print_ev(t_env *env)
{
	t_env *tmp;

	tmp  = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	t_env *ev;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		write(2, "not a tty!\n", 12);
		return (0);
	}
	ev = malloc (sizeof(t_env));
	// char *str = "     $HOME";
	// atexit(l);
	rl_catch_signals = 0;
	ft_getenv(ev, env);
	// print_ev(ev);
	while(1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		char *input = readline("GUMBALL$> ");
		if (!input)
			break;
		add_history(input);
		parser(input); 
	}
	// parser(str);
	return (0);
}
