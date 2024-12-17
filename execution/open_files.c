
// put your header here

#include "../minishell.h"

int	ambigious_check(t_redir *r, t_env *ev)
{
	t_redir	*tmp;

	if (!r || !ev)
		return (0);
	tmp = r;
	if (strcmp(tmp -> filename,"") == 0 )
	{
		printf("ambiguous redirect\n");
		return (1);
	}
	return (0);
}


int	check_file_in(char *file_name)
{
	struct stat	filestat;
	if (access(file_name, F_OK) == -1)
	{
		perror("Error accessing file");
		return (-1);
	}
	if (access(file_name, R_OK) == -1)
	{
		printf("Error: permission denied '%s'.\n", file_name);
		return (-1);
	}
	if (stat(file_name, &filestat) == -1)
	{
		perror("Error retrieving file info");
		return (-1);
	}
	if (S_ISDIR(filestat.st_mode))
	{
		fprintf(stderr, "Error: '%s' is a directory.\n", file_name);
		return (-1);
	}
	return (0);
}


int	check_file_out(char *file_name)
{
	struct stat	filestat;
	if (access(file_name, R_OK) == -1)
	{
		printf("Error: permission denied '%s'.\n", file_name);
		return (-1);
	}
	if (stat(file_name, &filestat) == -1)
	{
		perror("Error retrieving file info");
		return (-1);
	}
	if (S_ISDIR(filestat.st_mode))
	{
		fprintf(stderr, "Error: '%s' is a directory.\n", file_name);
		return (-1);
	}
	return (0);
}

int	open_it(t_redir **r, t_env *ev)
{
	if ((*r)->type == R_IN)
	{
		if (file_checkers((*r)->filename, R_IN))
			return (1);
		(*r)->fd = open((*r)->filename, O_RDONLY);
	}
	else if ((*r)->type == R_OUT)
	{
		(*r)->fd = open((*r)->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file_checkers((*r)->filename, R_OUT))
			return (1);
	}
	else if ((*r)->type == APP)
	{
		(*r)->fd = open((*r)->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file_checkers((*r)->filename, APP))
			return (1);
	}
	else if ((*r)->type == HER)
		check_on_herdoc((*r), ev);
	return (0);
}

int	open_files(t_command **commands, t_env *ev)
{
	t_command	*tmp;
	t_redir		*r;

	if (!*commands)
		return (1);
	tmp = *commands;
	while (*commands)
	{
		r = (*commands)->rederects;
		while (r)
		{
			if (ambigious_check(r, ev) == 1)
				return (1);
			if (open_it(&r, ev))
				return (1);
			r = r -> next;
		}
		*commands = (*commands)->next;
	}
	*commands = tmp;
	return (0);
}
