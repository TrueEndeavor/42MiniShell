/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_constructors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:00:33 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 09:01:46 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_P	*create_execcmd(void)
{
	t_execcmd_P		*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC_CMD;
	return ((t_cmd_P *)cmd);
}

t_cmd_P	*create_redircmd(t_cmd_P *subcmd, char *file, int mode, int fd)
{
	t_redircmd_P		*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR_CMD;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	cmd->permission = 0777;
	cmd->read_from = 0;
	cmd->write_into = 0;
	return ((t_cmd_P *)cmd);
}

void	set_read_from(t_redircmd_P *cmd, int readable)
{
	cmd->read_from = readable;
}

void	set_write_into(t_redircmd_P *cmd, int writable)
{
	cmd->write_into = writable;
}

t_cmd_P	*create_pipecmd(t_cmd_P *left, t_cmd_P *right)
{
	t_pipecmd_P		*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE_CMD;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd_P *)cmd);
}
