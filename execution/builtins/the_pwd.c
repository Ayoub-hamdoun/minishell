/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:38:21 by rallali           #+#    #+#             */
/*   Updated: 2024/12/21 18:10:06 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	the_pwd(t_redir *reder, t_env *env)
{
	char	*path;
	int		fd;

	(void)env;
	path = getcwd(NULL, 0);
	if (!path)
	{
		printf("minishell: pwd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: No such file or directory\n");
		return (1);
	}
	fd = rederctes_out(reder);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
	add(path);
	return (0);
}
