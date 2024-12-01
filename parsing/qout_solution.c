//fisrt solution for quote remouval - need more tests
void	remove_quotes(t_token **tokens)
{
	t_token	*current;
	char	*new_str;
	char	*tmp;
	char quote;
	int		i;
	int		start;

	current = *tokens;
	while (current)
	{
		if (current->q_type != NONE)
		{
			new_str = ft_strdup("");
			i = 0;
			while (current->str[i])
			{
				if (current->str[i] == '\'' || current->str[i] == '\"')
				{
					quote = current->str[i];
					i++;
					start = i;
					while (current->str[i] && current->str[i] != quote)
						i++;
					tmp = ft_substr(current->str, start, i - start); // Extract content inside quotes
					new_str = ft_strjoin(new_str, tmp);
					free(tmp);
					if (current->str[i] == quote)
						i++;
				}
				else
				{
					start = i;
					while (current->str[i] && current->str[i] != '\'' && current->str[i] != '\"')
						i++;
					tmp = ft_substr(current->str, start, i - start);
					new_str = ft_strjoin(new_str, tmp);
					free(tmp);
				}
			}
			free(current->str);
			current->str = new_str;
		}
		current = current->next;
	}
}