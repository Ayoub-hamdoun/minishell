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

	if (!lst){
		printf("no commands\n");
		return ;}
		
	while (lst)
	{
		printf("\nCOMMANDS : ---------------------------------\n");
		while (lst->args[i])
		{
			printf("[%s] \n", lst->args[i]);
			i++;
		}
		i = 0;
		printf ("\nis built in : %d, has expanded %d", lst->is_builtin, lst->flag);
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

void print_e(t_env *ev)
{
	t_env *temp = ev;
	while (temp)
	{
		if (temp->key && temp->value)
		{
			write(1, temp->key, ft_strlen(temp->key));
			 if (temp -> key  && temp->value)
				write(1, "=", 1);
			write(1, temp->value, ft_strlen(temp->value));
		}
		else if (temp->key && !temp->value)
			printf("%s\n", temp->key);
		temp = temp->next;
	}
}

void print_envp(char **envp)
{
	int i;
	i = 0;
	while (envp[i])
	{
		printf("%s\n",envp[i]);
		i++;
	}
}

int print_env(t_command *cmd, t_env *env)
{

	int fd;
	if (cmd -> args[1])
	{
		printf("minishell: No such file or directory\n");
		return (127);
	}
	fd = rederctes_out(cmd->rederects);

	while (env)
	{
			if (env->key && env->value)
			{
					// printf("%s=%s\n", env->key, env->value);
					write(fd, env->key, ft_strlen(env->key));
					if (ft_strcmp(env->key, "\0") != 0 && ft_strcmp(env->value, "\0") != 0)
						write(fd, "=", 1);
					write(fd, env->value, ft_strlen(env->value));
					if (ft_strcmp(env->key, "\0") != 0 && ft_strcmp(env->value, "\0") != 0)
						write(fd, "\n", 1);
			}
			else if (env->key && env->value)
				{
						write(fd, env->key, ft_strlen(env->key));
						write(fd, "\n", 1);
				}
		env = env->next;
	}
	return (0);
}