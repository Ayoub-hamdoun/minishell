/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/09/26 15:46:59 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	while(1)
	{
		char *input = readline("GUMBALL$>");
		add_history(input);
		parser(input);
	}
	// parser(argv[1]);
	return (0);
}
