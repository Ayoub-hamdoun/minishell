#include "../minishell.h"

char*	gettype(t_etype type)
{
	if (type == DOUBLE)
		return ("DOUBLE");
	else if (type == SINGLE)
		return "SINGLE";
	else if (type == NONE)
		return "NONE";
	else if (type == WORD)
		return "WORD";
	else if (type == R_IN)
		return "R_IN";
	else if (type == R_OUT)
		return "R_OUT";
	else if (type == APP)
		return "APP";
	else if (type == HER)
		return "HER";
	else if (type == ENV)
		return "ENV";
	else 
		return "PIPE";
}

void printtokens(t_token *lst)
{
	int i = 0;

	while (lst)
	{
		i++;
		printf("\nTOKEN : -------------------------\n");
		printf("%d; content [%s] ; type [%s] ; qoute type [%s]", i, lst->str, gettype(lst->token_type), gettype(lst->q_type));
		printf("\n---------------------------------\n");
		lst = lst->next;
	}
}
void printredirections(t_redir *lst)
{
	if (!lst)
		printf("\nno redirections");
	while (lst)
	{
		printf("\nREDIRECTIONS : ~~~~~~~~~~~~~~~~\n");
		printf("filename :[%s], file type [%s], in [%d], out [%d]", lst->filename, gettype(lst->type), lst->flag_in, lst->flag_out);
		printf("\n~~~~~~~~~~~~~~~~\n");
		lst = lst->next;
	}
}

void printcommnads(t_command *lst)
{
	int i = 0;

	if (!lst)
		// printf("no commands\n");
		return ;
	while (lst)
	{
		printf("\nCOMMANDS : ---------------------------------\n");
		while (lst->args[i])
		{
			printf("[%s] \n", lst->args[i]);
			i++;
		}
		i = 0;
		printf ("\n%d", lst->is_builtin);
		printredirections(lst->rederects);
		printf("\n---------------------------------\n");
		lst = lst->next;
	}
}


void exit_funcs(void)
{
	printf("\nSYNTAX ERROR\n");
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
