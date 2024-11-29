

//this is my all time best solution for the damn quotes problem
//i pushed it here to prevent conflict in my repo cause my smart ass forget to push the latest change done in the fokin 1337 cluster mac
//thnak me later


int is_special_char(char *trimmed, t_token **token_list, int pos)
{
	int h;
	char *str;

	str = NULL;
	if (trimmed[pos] == '|')
		create_token(token_list, "|", PIPE, NONE);
	else if (trimmed[pos] == '$')
	{
		h = pos;
		while (trimmed[pos] && trimmed[pos] != ' ' && trimmed[pos] != '\t')
			pos++;
		str = ft_substr(trimmed, h, pos - h);
		create_token(token_list, str, ENV, NONE);
	} 
	else if (trimmed[pos] == '>')
	{
		if (trimmed[pos + 1] == '>')
		{
			create_token(token_list, ">>", APP, NONE);
			pos++;
		}
		else
			create_token(token_list, ">", R_OUT, NONE);
	}
	else if (trimmed[pos] == '<')
	{
		if (trimmed[pos + 1] == '<')
		{
			create_token(token_list, "<<", HER, NONE);
			pos++;
		}
		else
			create_token(token_list, "<", R_IN, NONE);
	}
	pos++;
	if (str)
		free(str);
	return (pos);
}

int is_normal_word(char *trimmed, t_token **token_list, int pos)
{
	int start;
	char quote;
	char *str;
	t_etype qt;

	start = pos;
	quote = '\0';
	qt = NONE;
	while (trimmed[pos])
	{
		if ((trimmed[pos] == '\'' || trimmed[pos] == '\"') && !quote)
		{
			quote = trimmed[pos];
			if (quote == '\"')
				qt = DOUBLE;
			else if (quote == '\'')
				qt = SINGLE;
		}
		else if (trimmed[pos] == quote)
		{
			quote = '\0';
			qt = NONE;
		} 
		else if (quote == '\0' && (trimmed[pos] == ' ' || trimmed[pos] == '|' || trimmed[pos] == '>' || trimmed[pos] == '<'))
			break;
		pos++;
	}
	str = ft_substr(trimmed, start, pos - start);
	create_token(token_list, str, WORD, qt);
	if (str)
		free(str);
	return (pos);
}

void tokenizer(char *userInp, t_token **token_list)
{
	int i;
	char *trimmed;

	i = 0;
	trimmed = ft_strtrim(userInp, " \t");
	while (trimmed[i])
	{
		while (trimmed[i] == ' ' || trimmed[i] == '\t') // Skip white spaces
			i++;
		if (!trimmed[i])
			break;
		if (trimmed[i] == '|' || trimmed[i] == '>' || trimmed[i] == '<' || trimmed[i] == '$')
			i = is_special_char(trimmed, token_list, i);
		else
			i = is_normal_word(trimmed, token_list, i);
	}
	if (trimmed)
		free(trimmed);
}