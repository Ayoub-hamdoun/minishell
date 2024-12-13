/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/08 20:08:58 by ayhamdou         ###   ########.fr       */
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

void	fill_env(char **env)
{
	*env = malloc(sizeof(char *) * 2);
	env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin");
	env[1] = NULL;
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
	if (!env[0])
		fill_env(env);
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
