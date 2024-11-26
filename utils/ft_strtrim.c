/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:49:24 by rallali           #+#    #+#             */
/*   Updated: 2024/11/26 04:49:25 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static int	isin(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	if (!s1 || !set)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	i = 0;
	while (isin(set, s1[start]))
		start++;
	while (end >= 0 && isin(set, s1[end]))
		end--;
	if (end < start)
		return (ft_strdup(""));
	res = (char *) malloc((end - start + 1) + 1);
	if (!res)
		return (NULL);
	while (start <= end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}