/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:48:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/21 16:39:31 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_token_T	*minishell_compile(char *src)
{
	t_lexer_T	*lexer;
	t_token_T	*token_head;
	t_token_T	*tok;
	t_token_T	*prev_tok;
	
	prev_tok = NULL;
	lexer = init_lexer(src);
	tok = lexer_scan_token(lexer);
	token_head = tok;
	while (tok->type != T_LINEBREAK)
	{
		if (tok)
		if (prev_tok != NULL)
			prev_tok->next = tok;
		prev_tok = tok;
		tok = lexer_scan_token(lexer);
		tok->next = NULL;
	}
	prev_tok->next = tok;
	tok->next = NULL;
	return (token_head);
}

void	display_new_prompt(t_core_struct *general)
{
	char		*prompt;
	int			len;
	t_token_T	*token_head;
	t_cmd_P	*   root;

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
		token_head = minishell_compile(prompt);
		root = parse_cmd(&token_head);
		// built-ins
		if (root->type == EXEC_CMD)
		{
			match_builtin(root, general);
		}
		if(fork1() == 0)
			run_cmd(root, general);
		wait(0);
		printf("\n");
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_core_struct   *general;
	
	general = NULL;
	if (ac > 1)
	{
		panic("No input required. \
			[Usage] Just launch with ./minishell");
		exit (1);
	}
	(void) av;
	general = malloc(1 * sizeof(t_core_struct));
	general->envp = envp;
	display_new_prompt(general);
	return (0);
}
