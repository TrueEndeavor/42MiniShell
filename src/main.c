/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:48:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/02 19:58:01 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_compile(char *src)
{
	t_lexer_T	*lexer;
	t_token_T	*tok;

	lexer = init_lexer(src);
	tok = lexer_scan_token(lexer);
	while (tok->type != LINEBREAK)
	{
		printf("TOK(%s) (%d)\n", tok->value, tok->type);
		tok = lexer_scan_token(lexer);
	}
}

void	display_new_prompt(void)
{
	char	*prompt;
	int		len;

	while (1)
	{
		prompt = readline("jollyshell$> ");
		if (prompt == NULL)
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
		len = ft_strlen(prompt);
		if (len > 0 && prompt[len - 1] == '\n')
		{
			prompt[len - 1] = '\0';
		}
		add_history(prompt);
		if (strcmp(prompt, "exit") == 0 || strcmp(prompt, "quit") == 0)
		{
			break ;
		}
		minishell_compile(prompt);
	}
}

int	main(int ac, char *av[])
{
	if (ac > 1)
	{
		display_error("No input required. \
			[Usage] Just launch with ./minishell");
		exit (1);
	}
	(void) av;
	display_new_prompt();
	return (0);
}
