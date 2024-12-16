/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:24:47 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/16 20:37:03 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(const char *str, char delimiter)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] == delimiter)
			i++;
		if (str[i] && str[i] != delimiter)
			c++;
		while (str[i] && str[i] != delimiter)
			i++;
	}
	return (c);
}

// static char	**//free_tab(char **tab)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (tab[i])
// 		//free(tab[i++]);
// 	//free(tab);
// 	return (NULL);
// }

static char	*ret_sub(const char *s1, int *index, char c)
{
	char	*copy;
	size_t	word_len;
	int		i;

	word_len = 0;
	while (s1[*index] == c)
		(*index)++;
	i = *index;
	while (s1[i] && s1[i] != c)
	{
		word_len++;
		i++;
	}
	copy = ft_malloc(sizeof(char) * (word_len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[*index] && s1[*index] != c)
		copy[i++] = s1[(*index)++];
	copy[i] = '\0';
	return (copy);
}

char	**ft_split(char *s, char c)
{
	char	**arr;
	int		index;
	int		wc;
	int		i;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	wc = count_words(s, c);
	arr = ft_malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	while (i < wc)
	{
		arr[i] = ret_sub(s, &index, c);
		if (!arr[i])
			return (arr);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
