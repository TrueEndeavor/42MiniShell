/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:48:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/12 13:44:43 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

t_token_T	*minishell_compile(char *src)
{
	t_lexer_T	*lexer;
	t_token_T	*token_head;
	t_token_T	*tok;
	t_token_T	*prev_tok;
	
	prev_tok = NULL;
	lexer = init_lexer(src);
	tok = lexer_scan_token(lexer);
	if (tok == NULL)
		return (NULL);
	token_head = tok;
	while (tok->type != T_LINEBREAK)
	{
		if (prev_tok != NULL)
			prev_tok->next = tok;
		prev_tok = tok;
		tok = lexer_scan_token(lexer);
		if (tok == NULL)
		{
			ft_free_tok_list(&token_head);
			return (NULL);
		}
		tok->next = NULL;
	}
	prev_tok->next = tok;
	tok->next = NULL;
	return (token_head);
}

int	display_new_prompt(t_core_struct *core)
{
	char		*prompt;
	//int			len;
	t_token_T	*token_head;
	t_cmd_P	*   root;
	int         child_pid;
	int         status;

	prompt = NULL;
	g_exit_code = 0;
	while (1)
	{
		setup_readline_signals();
		if (isatty(STDIN_FILENO))
			prompt = readline("jollyshell$> ");
		if (prompt != NULL)
		{
			if (*prompt)
			{
				add_history(prompt);
				if (strcmp(prompt, "exit") == 0 || strcmp(prompt, "quit") == 0)
				{
					break ;
				}
				token_head = minishell_compile(prompt);
				core->token_head = &token_head;
				print_token_list(*core->token_head);
			    if (syntax_analyzer(*core->token_head))
				{
					root = parse_cmd(core);
					// normal commands
					if (root->type == EXEC_CMD || root->type == PIPE_CMD)
					{
						if (!match_builtin(root, core))
						{
							setup_mother_signals();
							run_cmd(root, core);
						}
					}
					else
					{
						printf("// built-ins\n");
						// doesnt ned fork
						child_pid = fork1();
						if(child_pid == 0)
						{
							run_cmd(root, core);
						}
						waitpid(child_pid, &status, 0);
						//wait(0);
					}
				}
				else
				{
					printf ("error during check of arguments, freeing...\n");
					ft_free_tok_list(core->token_head);
					//printf("syntax check finished\n");
					//free everything
				}
				
				printf ("g_exit_code: %d\n", g_exit_code);
			}
		}
		else // Ctrl+D
		{
			ft_free_env(core->env_list);
			free(core);
			ft_printf("exit from the prompt level\n");
			// free everything
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	(void) av;
	t_core_struct   *core;
	int ret_value;
	core = NULL;
	
	
	if (ac > 1)
	{
		panic("No input required. \
			[Usage] Just launch with ./minishell");
		exit (1);
	}
	core = malloc(1 * sizeof(t_core_struct));
	core->env_list = init_env(envp);
	printf("address of el in main %p\n", &core->env_list);
	ft_update_SHLVL(core);
	ret_value = display_new_prompt(core);
	return (ret_value);
}
