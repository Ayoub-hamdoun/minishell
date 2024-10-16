/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:00:50 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/10/16 10:12:06 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	fix_len(char *str, int start)
{
	int	i;

	i = 0;
	while (str[start])
	{
		i++;
		start++;
	}
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*subs;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len + start > ft_strlen(s))
		len = fix_len((char *)s, start);
	subs = (char *)malloc (len * sizeof(char) + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = s[i + start];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
