/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:03 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/08 11:57:49 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tok_list(t_token_T **token_head)
{
	t_token_T	*helper;

	helper = NULL;
	if (token_head)
	{
		while ((*token_head) != NULL)
		{
			helper = (*token_head)->next;
			free((*token_head)->value);
			free(*token_head);
			(*token_head) = helper;
		}
	}
}

void	ft_free_env(t_env_list *env)
{
	t_env_list	*next;

	if (env)
	{
		while (env != NULL)
		{
			next = env->next;
			if (env->name)
			{
				free(env->name);
			}
			if (env->value)
			{
				free(env->value);
			}
			free(env);
			env = next;
		}
	}
}

void	ft_free_ecmd(t_cmd_P *cmd)
{
	t_execcmd_P		*ecmd;

	ecmd = (t_execcmd_P *) cmd;
	free(ecmd);
}

void	ft_free_heredoc(t_cmd_P *cmd)
{
	t_herecmd_P	*hcmd;

	hcmd = (t_herecmd_P *) cmd;
	free(hcmd->filename);
	ft_free_cmd(hcmd->cmd);
	free(hcmd);
}

void	ft_free_cmd(t_cmd_P *cmd)
{
	t_redircmd_P	*rcmd;
	t_pipecmd_P		*pcmd;

	if (cmd->type == PIPE_CMD)
	{
		pcmd = (t_pipecmd_P *)cmd;
		ft_free_cmd(pcmd->left);
		ft_free_cmd(pcmd->right);
		free(pcmd);
	}
	else if (cmd->type == REDIR_CMD)
	{
		rcmd = (t_redircmd_P *) cmd;
		ft_free_cmd(rcmd->cmd);
		free(rcmd);
	}
	else if (cmd->type == HERE_CMD)
		ft_free_heredoc(cmd);
	else if (cmd->type == EXEC_CMD)
		ft_free_ecmd(cmd);
}
