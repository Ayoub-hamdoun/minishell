/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/19 21:13:59 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_exit_status;

void	handle_sig(int sig)
{
	(void)sig;
	g_exit_status = 127;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// void	fill_env(char **env)
// {
// 	*env = ft_ft_malloc(sizeof(char *) * 2);
// 	env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
// 							/usr/local/munki:/Library/Apple/usr/bin");
// 	env[1] = NULL;
// }
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
	// if (argc > 1)
	// 	return (0);
	// atexit(f);
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
		parser(input, ev);
	}
	free_all();
	return (0);
}
