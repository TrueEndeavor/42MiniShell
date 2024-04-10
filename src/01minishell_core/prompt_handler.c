/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:33:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 14:19:19 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_cmd_P *root, t_core_struct *core)
{
	int		status;
	pid_t	child_pid;

	setup_mother_signals();
	if (handle_heredoc(core, root, 0))
	{
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
	else
		return ;
}

void	process_user_input(t_core_struct *core, char *prompt)
{
	t_token_T	*token_head;
	t_cmd_P		*root;

	root = NULL;
	add_history(prompt);
	token_head = minishell_compile(prompt);
	if (!token_head)
	{
		core->exit_code = 2;
		return ;
	}
	if (token_head != NULL)
		core->token_head = &token_head;
	if (syntax_analyzer(core))
	{
		root = parse_cmd(core);
		if ((root->type == EXEC_CMD) && !(((t_execcmd_P *) root)->argv[0]))
			return ;
		if (!match_builtin(root, core, prompt))
			execute_command(root, core);
	}
	else
		ft_free_tok_list(core->token_head);
	if (root)
		ft_free_cmd(root);
	ft_free_tok_list(core->token_head);
	free(prompt);
}

char	*get_prompt_interactive_mode(t_core_struct *core)
{
	char	*prompt;

	prompt = NULL;
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
		if (prompt == NULL)
		{
			process_eof(core);
			return (core->exit_code);
		}
		if (is_all_whitespace(prompt) || !(prompt[0]))
		{
			continue ;
		}
		process_user_input(core, prompt);
	}
	exit(core->exit_code);
}
