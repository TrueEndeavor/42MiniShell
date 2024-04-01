/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_printers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:11:57 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 07:14:00 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"
#include <stdio.h>

void	print_execcmd(t_cmd_P *cmd)
{
	t_execcmd_P	*execcmd;
	int			i;

	i = 0;
	execcmd = (t_execcmd_P *)cmd;
	printf("Type: EXEC_CMD\n");
	while (i < MAXARGS)
	{
		printf("argv: -%s-\n", execcmd->argv[i]);
		i++;
	}
}

void	print_redircmd(t_cmd_P *cmd)
{
	t_redircmd_P	*redirectcmd;

	redirectcmd = (t_redircmd_P *)cmd;
	printf("Type: REDIR_CMD\n");
	printf("File: %s\n", redirectcmd->file);
	printf("Mode: %d\n", redirectcmd->mode);
	printf("File Descriptor: %d\n", redirectcmd->fd);
	if (redirectcmd->cmd != NULL)
	{
		printf("Sub-command:\n");
		print_cmd (redirectcmd->cmd);
	}
	printf("Permission: %d\n", redirectcmd->permission);
	printf("Read from: %d\n", redirectcmd->read_from);
	printf("Write into: %d\n", redirectcmd->write_into);
}

void	print_pipecmd(t_cmd_P *cmd)
{
	t_pipecmd_P	*pipecmd;

	pipecmd = (t_pipecmd_P *)cmd;
	printf("Type: PIPE_CMD\n");
	printf("Left command:\n");
	print_cmd(pipecmd->left);
	printf("Right command:\n");
	print_cmd(pipecmd->right);
}

void	print_herecmd(t_cmd_P *cmd)
{
	t_herecmd_P	*herecmd;

	herecmd = (t_herecmd_P *)cmd;
	printf("type: HERE_CMD\n");
	printf("delimiter: %s\n", herecmd->delimiter);
	if (herecmd->cmd != NULL)
	{
		printf("sub-command:\n");
		print_cmd(herecmd->cmd);
	}
}

void	print_cmd(t_cmd_P *cmd)
{
	if (cmd == NULL)
	{
		printf("Command is NULL\n");
		return ;
	}
	printf("command type = %d\n", cmd->type);
	if (cmd->type == EXEC_CMD)
		print_execcmd(cmd);
	else if (cmd->type == REDIR_CMD)
		print_redircmd(cmd);
	else if (cmd->type == PIPE_CMD)
		print_pipecmd(cmd);
	else if (cmd->type == HERE_CMD)
		print_herecmd(cmd);
	else
		printf ("Unknown command type\n");
}
