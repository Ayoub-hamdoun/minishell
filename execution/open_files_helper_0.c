
#include "../minishell.h"

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
		free(str);
		return (res);
	}
	return (str);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
	{
		perror("stat\n");
		return (-1);
	}
	if (S_ISDIR(path_stat.st_mode))
		return (-1);
	return (0);
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
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		str = readline("herdoc> ");
		if (!str || ft_strcmp(str, r->filename) == 0)
		{
			free (str);
			close (0);
			str = NULL;
			close (pipe);
			break ;
		}
		str = is_expand(str, exp_flag, ev);
		write (pipe, str, ft_strlen(str));
		write (pipe, "\n", 1);
		free(str);
	}
	dup2(hold, STDIN_FILENO);
}
