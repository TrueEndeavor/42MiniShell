/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:03 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/19 15:24:11 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tok_list(t_token_T **token_head)
{
	t_token_T	*helper;

	helper = NULL;
	if (token_head)
	{
		//printf ("commencing free of token list\n");
		while ((*token_head) != NULL)
		{
			helper = (*token_head)->next;
			//printf("value of current head: %s\n", (*token_head)->value);
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
			free(env->name);
			free(env->value);
			free(env);
			env = next;
		}
	}
}

void	ft_free_cmd(t_cmd_P *cmd)
{
	t_execcmd_P		*ecmd;
	t_redircmd_P	*rcmd;
	t_pipecmd_P		*pcmd;
	t_herecmd_P		*hcmd;

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
	{
		hcmd = (t_herecmd_P *) cmd;
		ft_free_cmd(hcmd->cmd);
		free(hcmd);
	}
	else if (cmd->type == EXEC_CMD)
	{
		ecmd = (t_execcmd_P *) cmd;
		free(ecmd);
	}
}
