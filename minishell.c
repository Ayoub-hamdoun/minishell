/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/26 18:06:34 by ayhamdou         ###   ########.fr       */
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
		add_history(input);
		parser(input); 
	}
	// parser(str);
	return (0);
}
