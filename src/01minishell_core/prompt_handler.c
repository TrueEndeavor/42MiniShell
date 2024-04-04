/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:33:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/31 16:33:31 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_cmd_P *root, t_core_struct *core)
{
	int	status;
	pid_t	child_pid;

	setup_mother_signals();
	child_pid = fork1();
	if (child_pid == 0)
	{
		setup_child_signals();
		run_cmd(root, core, root);
	}
	else
	{
		core->exit_code = waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
			core->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			core->exit_code = process_signals_in_child(status);
	}
}

void	process_user_input(t_core_struct *core, char *prompt)
{
	t_token_T	*token_head;
	t_cmd_P		*root;

	root = NULL;
	add_history(prompt);
	token_head = minishell_compile(prompt);
	if (token_head != NULL)
		core->token_head = &token_head;
	#if DEBUG
	print_token_list(token_head);
	#endif
	if (syntax_analyzer(core))
	{
		root = parse_cmd(core);
		if (!match_builtin(root, core, prompt))
			execute_command(root, core);
	}
	else
	{
		#if DEBUG
		printf ("error during check of arguments, freeing...\n");
		#endif
		ft_free_tok_list(core->token_head);
	}
	if (root)
		ft_free_cmd(root);
	ft_free_tok_list(core->token_head);
	free(prompt);
	#if DEBUG
	printf ("core->exit_code: %d\n", core->exit_code);
	#endif
}

	char	*get_prompt_interactive_mode(t_core_struct *core)
{
	char	*prompt;

	prompt = NULL;
	setup_readline_signals();
	//if (isatty(STDIN_FILENO))
	//{
		prompt = readline("jollyshell$> ");
		//core->exit_code = EXIT_SUCCESS;
		if (g_signum != 0)
		{
			core->exit_code += (g_signum + 128);
			g_signum = 0;
		}
	//}
	return (prompt);
}

int	display_new_prompt(t_core_struct *core)
{
	char		*prompt;

	prompt = NULL;
	g_signum = 0;
	while (1)
	{
		prompt = get_prompt_interactive_mode(core);
		if (prompt == NULL) //eof - Ctrl + D
		{
			process_eof(core);
			return (1);
		}
		if (is_all_whitespace(prompt) || !(prompt[0]))
		{
			continue ;
		}
		process_user_input(core, prompt);
	}
	exit(core->exit_code);
}
