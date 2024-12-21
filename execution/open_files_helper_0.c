
#include "../minishell.h"

void	handle_here_sig(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_exit_status = SIGINT;
	}
	exit_status(-1);
}

void	handle_b_slash(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}

void	check_on_herdoc(t_redir *r, t_env *ev)
{
	int	ld[2];
	int	exp_flag;

	if (r->q_type != NONE)
		exp_flag = 1;
	else
		exp_flag = 0;
	if (pipe(ld) == -1)
		return ;
	lherdoc(r, ld[1], exp_flag, ev);
	r->fd = ld[0];
}

char	*is_expand(char *str, int exp_flag, t_env *ev)
{
	char	*res;
	char	*expanded;

	if (!exp_flag)
	{
		expanded = NULL;
		res = ft_strdup("");
		expand_it(str, &res, &expanded, ev);
		return (res);
	}
	return (str);
}

int	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	lherdoc(t_redir *r, int pipe, int exp_flag, t_env *ev)
{
	char	*str;
	int		hold;

	str = NULL;
	hold = dup(STDIN_FILENO);
	while (1)
	{
		signal(SIGINT, handle_here_sig);
		signal(SIGQUIT, SIG_IGN);
		str = readline("herdoc> ");
		if (!str)
            break;
        add(str);
        if (ft_strcmp(str, r->filename) == 0)
        {
            free(str);
            close(0);
            close(pipe);
            break;
        }
		str = is_expand(str, exp_flag, ev);
		write (pipe, str, ft_strlen(str));
	}
	dup2(hold, STDIN_FILENO);
	close(hold);
	close(pipe);
}
