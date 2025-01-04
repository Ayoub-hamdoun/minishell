/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grbdg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:16:34 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/12/22 19:43:24 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_grbdg	**get_grbdg(void)
{
	static t_grbdg	*grbdg;

	return (&grbdg);
}

void	add(void *ptr)
{
	t_grbdg	**grbdg;
	t_grbdg	*current;
	t_grbdg	*new_node;

	grbdg = get_grbdg();
	current = *grbdg;
	while (current)
	{
		if (current->ptr == ptr)
			return ;
		current = current->next;
	}
	new_node = malloc(sizeof(t_grbdg));
	if (!new_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->next = *grbdg;
	*grbdg = new_node;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	add(ptr);
	return (ptr);
}

void	free_all(void)
{
	t_grbdg	**grbdg;
	t_grbdg	*curr;
	t_grbdg	*next;

	grbdg = get_grbdg();
	curr = *grbdg;
	while (curr)
	{
		next = curr->next;
		if (curr->ptr)
			free(curr->ptr);
		free(curr);
		curr = next;
	}
	*grbdg = NULL;
}
