/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:13 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/21 16:36:21 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork1(void)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void	runcmd_exec(t_cmd_P *cmd, t_core_struct *general)
{
	t_execcmd_P	*ecmd;

	ecmd = (t_execcmd_P *) cmd;
	if (ecmd->argv[0] == 0)
		exit (1);
	printf("######RUNCMD_EXEC######\n");
	printf("THE COMMAND IS = %s\n", ecmd->argv[0]);
	ft_execute(ecmd->argv, general->envp);
	dprintf(2, "exec %s failed\n", ecmd->argv[0]);
}

void	runcmd_redir(t_cmd_P *cmd, t_core_struct *general)
{
	t_redircmd_P	*rcmd;
	//int     fd;

	rcmd = (t_redircmd_P *) cmd;
	if (rcmd->write_into == 1 || rcmd->read_from == 1)	
		close(rcmd->fd);
	if ((open (rcmd->file, rcmd->mode, rcmd->permission)) < 0)
	{
		dprintf(2, "open %s failed\n", rcmd->file);
		exit(0);
	}
/* 	if (rcmd->write_into == 1)
		dup2(fd, rcmd->fd);
	else
		close(fd);
 */	run_cmd(rcmd->cmd, general);
}

void	runcmd_pipe(t_cmd_P *cmd, t_core_struct *general)
{
	t_pipecmd_P	*pcmd;
	int p[2];

	pcmd = (t_pipecmd_P *)cmd;
	if (pipe(p) < 0)
		panic("pipe");
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->left, general);
	}
	if (fork1() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->right, general);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

void	run_cmd(t_cmd_P *cmd, t_core_struct *general)
{
	//int				p[2];

	printf("run_cmd::: cmd->type=%d\n", cmd->type);
	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC_CMD)
	{
		
		runcmd_exec(cmd, general);
	}
	if (cmd->type == REDIR_CMD)
		runcmd_redir(cmd, general);
	if (cmd->type == PIPE_CMD)
		runcmd_pipe(cmd, general);
	panic ("runcmd");
	exit (1);
}
