/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:13 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/07 18:13:46 by lannur-s         ###   ########.fr       */
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

void	run_cmd_exec(t_cmd_P *cmd)
{
	ecmd = (t_execcmd_P *) cmd;
	if (ecmd->argv[0] == 0)
		exit();
	exec(ecmd->argv[0], ecmd->argv);
	printf(2, "exec %s failed\n", ecmd->argv[0]);
}

void	run_cmd_redir(t_cmd_P *cmd)
{
	rcmd = (t_redircmd_P *) cmd;
	close(rcmd->fd);
	if (open (rcmd->file, rcmd->mode) < 0)
	{
		printf(2, "open %s failed\n", rcmd->file);
		exit();
	}
	runcmd(rcmd->cmd);
}

void	run_cmd_pipe(t_cmd_P *cmd)
{
	pcmd = (t_pipecmd_P *)cmd;
	if (pipe(p) < 0)
		panic("pipe");
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left);
	}
	if (fork1() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right);
	}
	close(p[0]);
	close(p[1]);
	wait();
	wait();
}

void	run_cmd(t_cmd_P *cmd)
{
	int				p[2];
	t_execcmd_P		*ecmd;
	t_pipecmd_P		*pcmd;
	t_redircmd_P	*rcmd;

	if (cmd == 0)
		exit();
	if (cmd->type == EXEC_CMD)
		runcmd_exec(cmd);
	if (cmd->type == REDIR_CMD)
		runcmd_redir(cmd);
	if (cmd->type == PIPE_CMD)
		runcmd_pipe(cmd);
	panic ("runcmd");
	exit();
}
