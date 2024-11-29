/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayhamdou <ayhamdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:39:55 by ayhamdou          #+#    #+#             */
/*   Updated: 2024/11/28 17:01:51 by ayhamdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
