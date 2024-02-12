/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_constructors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:00:33 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/09 10:14:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*create_execcmd(void)
{
	t_execcmd_P		*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC_CMD;
	return ((t_cmd_P *)cmd);
}

t_cmd_P	*create_redircmd(t_cmd_P *subcmd, char *file, int mode, int fd)
{
	t_redircmd_P		*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR_CMD;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd_P *)cmd);
}

t_cmd_P	*create_pipecmd(t_cmd_P *left, t_cmd_P *right)
{
	t_pipecmd_P		*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd_P *)cmd);
}
