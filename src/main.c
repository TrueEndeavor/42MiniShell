/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:48:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/21 10:49:32 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_token_T	*minishell_compile(char *src)
{
	t_lexer_T	*lexer;
	t_token_T	*token_head;
	t_token_T	*tok;
	t_token_T	*prev_tok;
/* 	t_parser_P  *parser;
	t_AST_P     *root;
 */	
	prev_tok = NULL;
	lexer = init_lexer(src);
//	parser = init_parser(lexer);
//	root = parser_parse(parser);
//	printf(":%p\n", root);
	tok = lexer_scan_token(lexer);
	token_head = tok;
	while (tok->type != T_LINEBREAK)
	{
		if (tok)
		//printf("TOK(%s) (%d)\n", tok->value, tok->type);
		//printf("%s\n", token_to_str(tok));
		if (prev_tok != NULL)
			prev_tok->next = tok;
		prev_tok = tok;
		tok = lexer_scan_token(lexer);
		tok->next = NULL;
	}
	prev_tok->next = tok;
	tok->next = NULL;
	//printf("TOK(%s) (%d)\n", tok->value, tok->type);
	return (token_head);
}

void	display_new_prompt(t_general *general)
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
//		printf("<<<START PARSING>>>");
		//print_token_list(token_head);
		root = parse_cmd(&token_head);
		if(fork1() == 0)
			run_cmd(root, general);
		wait(0);
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_general   *general;
	
	general = NULL;
	if (ac > 1)
	{
		display_error("No input required. \
			[Usage] Just launch with ./minishell");
		exit (1);
	}
	(void) av;
	// Add the env to main data structure
	// For now void it
	general = malloc(1 * sizeof(t_general));
	general->envp = envp;
	display_new_prompt(general);
	return (0);
}
