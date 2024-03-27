/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:48:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/27 14:01:39 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signum;

t_env_list	*create_dummy_env()
{	
	char	*name;
	char	*value;

	name = ft_strdup("creators");
	if (!name)
		return (NULL);
	value = ft_strdup("Latha and Rico");
	if (!value)
	{
		free (name);
		return (NULL);
	}
	return (ft_lstnew_env(name, value));
}

t_token_T	*minishell_compile(char *src)
{
	t_lexer_T	*lexer;
	t_token_T	*token_head;
	t_token_T	*tok;
	t_token_T	*prev_tok;
	
	prev_tok = NULL;
	lexer = init_lexer(src);
	tok = lexer_scan_token(lexer);
	if ((tok == NULL) || (tok->type == T_LINEBREAK))
	{
		free(lexer);
		return (NULL);
	}
	token_head = tok;
	while (tok->type != T_LINEBREAK)
	{
		if (prev_tok != NULL)
			prev_tok->next = tok;
		prev_tok = tok;
		tok = lexer_scan_token(lexer);
		if (tok == NULL)
		{
			free(lexer);
			ft_free_tok_list(&token_head);
			return (NULL);
		}
		tok->next = NULL;
	}
	prev_tok->next = tok;
	tok->next = NULL;
	free(lexer);
	return (token_head);
}

int	display_new_prompt(t_core_struct *core)
{
	char		*prompt;
	t_token_T	*token_head;
	t_cmd_P		*root;
	
	prompt = NULL;
	root = NULL;
	g_signum = 0;
	while (1)
	{
		setup_readline_signals();
		if (isatty(STDIN_FILENO))
		{
			prompt = readline("jollyshell$> ");
			if (g_signum != 0)
			{
				core->exit_code += (g_signum + 128);
				g_signum = 0;
			}
		}
		if (prompt != NULL)
		{
			if (*prompt)
			{
				add_history(prompt);
				token_head = minishell_compile(prompt);
				core->token_head = &token_head;
				print_token_list(*core->token_head);
				printf("token list check\n");
			    if (syntax_analyzer(core))
				{
					root = parse_cmd(core);					
					// normal commands
					if (!match_builtin(root, core, prompt))
					{
						setup_mother_signals();
						int status;
						int child_pid;
						int last_status;
						child_pid = fork1();
						if(child_pid == 0)
						{
							// child signals
							setup_child_signals();
							run_cmd(root, core, root);
						}
						else 
						{ 
							last_status = waitpid(child_pid, &status, 0);
							if (WIFEXITED(status)) 
							{
								last_status = WEXITSTATUS(status);
//								printf("Exit status of the child was %d\n", last_status);
							}
							else if (WIFSIGNALED(status))
							{
						 		last_status = WTERMSIG(status);
//								printf("...Exit status of the child was %d\n", last_status);
								if (last_status == SIGTERM)
									write(1, "\n", 1);
								else if (last_status == SIGQUIT)
									write(2, "Quit (core dumped)\n", 18);
								last_status += 128;
							}
							core->exit_code = last_status;
						}
					}
				}
				else
				{
					printf ("error during check of arguments, freeing...\n");
					ft_free_tok_list(core->token_head);
				}
				if (root)
					ft_free_cmd(root);
				ft_free_tok_list(core->token_head);
				free(prompt);
				printf ("core->exit_code: %d\n", core->exit_code);
			}
		}
		else // Ctrl+D
		{
			ft_free_env(core->env_list);
			free(core);
			printf("exit\n");
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	(void) av;
	(void) envp;
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
	core->exit_code = EXIT_SUCCESS;
	if (getenv("USER") == NULL)
		core->env_list = create_dummy_env();
	else
	{
		core->env_list = init_env(envp);
		ft_update_shlvl(core);
	}
	ret_value = display_new_prompt(core);
	return (ret_value);
}
