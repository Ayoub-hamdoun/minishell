/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 17:29:40 by ayhamdou         ###   ########.fr       */
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

void	check_tty(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		write(2, "not a tty!\n", 12);
		exit (1);
	}
}

void	check_env(char	**env)
{
	if (!env[0])
	{
		printf("no env set\n");
		exit (1);
	}
}

void	check_signal(void)
{
	if (g_exit_status == SIGINT)
	{
		g_exit_status = 0;
		exit_status(1);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_env	*ev;
	char	*input;

	(void)argc;
	(void)argv;
	check_tty();
	rl_catch_signals = 0;
	check_env(env);
	ev = ft_malloc (sizeof(t_env));
	dup_env(ev, env);
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		add(malloc(1));
		input = readline("minishell$> ");
		add(input);
		if (!input)
			ft_exit(NULL);
		add_history(input);
		check_signal();
		parser(input, ev);
	}
	return (free_all(), 0);
}
