/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/27 08:11:57 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>


// void l()
// {
// 	system("leaks minishell");
// }

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	// char *str = "     $HOME";
	// atexit(l);
	while(1)
	{
		char *input = readline("GUMBALL$> ");
		if (!input)
			break;
		add_history(input);
		parser(input); 
	}
	// parser(str);
	return (0);
}
