
int	update_var(t_env *env, char *key, char *value, int append)
{
	char	*new_value;

	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			if (append == 0)
			{
				if (env->value)
				{
					new_value = malloc(strlen(env->value) + strlen(value) + 1);
					if (!new_value)
					{
						perror("Failed to allocate memory for value append");
						return (1);
					}
					strcpy(new_value, env->value);
					strcat(new_value, value);
					free(env->value);
					env->value = new_value;
				}
				else
					env->value = value;
			}
			else
			{
				free(env->value);
				env->value = value;
			}
			free(key);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
