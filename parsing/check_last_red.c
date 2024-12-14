// put your header

#include "../minishell.h"

void	check_last(t_command *token)
{
	t_redir	*last_in;
	t_redir	*redir;

	if (!token)
		return ;
	while (token)
	{
		last_in = NULL;
		redir = token->rederects;
		while (redir)
		{
			if (redir->type == R_IN || redir->type == HER)
			{
				if (last_in)
					last_in->flag_in = 0;
				last_in = redir;
			}
			redir = redir->next;
		}
		if (last_in)
			last_in->flag_in = 1;
		token = token->next;
	}
}

void	check_last_out(t_command *token)
{
	t_redir	*last_out;
	t_redir	*redir;

	if (!token)
		return ;
	while (token)
	{
		last_out = NULL;
		redir = token->rederects;
		while (redir)
		{
			if (redir->type == R_OUT || redir->type == APP)
			{
				if (last_out)
					last_out->flag_out = 0;
				last_out = redir;
			}
			redir = redir->next;
		}
		if (last_out)
			last_out->flag_out = 1;
		token = token->next;
	}
}
