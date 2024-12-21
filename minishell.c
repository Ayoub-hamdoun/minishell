/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/20 22:19:56 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_exit_status;

void	handle_sig(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void f()
{
	system("leaks minishell");
}
int	main(int argc, char *argv[], char **env)
{
	t_env	*ev;
	char	*input;

	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		write(2, "not a tty!\n", 12);
		return (0);
	}
	rl_catch_signals = 0;
	if (!env[0])
	{
		printf("no env set\n");
		return (1);
	}
	ev = ft_malloc (sizeof(t_env));
	dup_env(ev, env);
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		add(malloc(1));
		input = readline("GUMBALL$> ");
		add(input);
		if (!input)
			ft_exit(NULL);
		add_history(input);
		if (g_exit_status == SIGINT)
		{
			g_exit_status = 0;
			exit_status(1);
		}
		parser(input, ev);
	}
	free_all();
	return (0);
}
