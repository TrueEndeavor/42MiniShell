/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:48:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/07 12:50:26 by trysinsk         ###   ########.fr       */
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
	token_head = tok;
	while (tok->type != T_LINEBREAK)
	{
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

void	display_new_prompt(t_core_struct *core)
{
	char		*prompt;
	int			len;
	t_token_T	*token_head;
	t_cmd_P	*   root;

	prompt = NULL;
	g_exit_code = 0;
	while (1)
	{
		// Signals: Readline
		set_signal_receiver_readline();
		prompt = readline("jollyshell$> ");
		if (prompt[0] == '\0')
		{
			//perror("readline");
			exit (EXIT_FAILURE);
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
		core->token_head = &token_head;
print_token_list(*core->token_head);
	    if (syntax_analyzer(*core->token_head))
		{
			root = parse_cmd(core);
		// built-ins
		if (root->type == EXEC_CMD)
		{
		printf("parent pid: %d\n", getpid());
			if (!match_builtin(root, core))
			{
				if(fork1() == 0)
				{
					printf("child pid: %d\n", getpid());
					run_cmd(root, core);
				}
				g_exit_code = 0;
				waitpid(-1, &g_exit_code, 0);
				//wait(0);
			}
		}
		else
		{
			printf("parent pid: %d\n", getpid());
			if(fork1() == 0)
			{
				printf("child pid: %d\n", getpid());
				run_cmd(root, core);
			}
			g_exit_code = 0;
			waitpid(-1, &g_exit_code, 0);
			//wait(0);
		}
		}
		else
		{
			printf("syntax check finished\n");
			//free everything
		}
			printf ("g_exit_code: %d\n", g_exit_code);
	}
}

int	main(int ac, char *av[], char **envp)
{
	(void) av;
	t_core_struct   *core;
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
	display_new_prompt(core);
	return (0);
}
