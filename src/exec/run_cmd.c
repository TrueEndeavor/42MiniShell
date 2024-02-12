/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:13 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/12 09:16:27 by lannur-s         ###   ########.fr       */
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

void	runcmd_exec(t_cmd_P *cmd)
{
	t_execcmd_P	*ecmd;

	ecmd = (t_execcmd_P *) cmd;
	if (ecmd->argv[0] == 0)
		exit (1);
	exec(ecmd->argv[0], ecmd->argv);
	dprintf(2, "exec %s failed\n", ecmd->argv[0]);
}

void	runcmd_redir(t_cmd_P *cmd)
{
	t_redircmd_P	*rcmd;

	rcmd = (t_redircmd_P *) cmd;
	close(rcmd->fd);
	/*if (open (rcmd->file, rcmd->mode) < 0)
	{
		printf(2, "open %s failed\n", rcmd->file);
		exit();
	}*/
	run_cmd(rcmd->cmd);
}

void	runcmd_pipe(t_cmd_P *cmd)
{
	t_pipecmd_P	*pcmd;

	pcmd = (t_pipecmd_P *)cmd;
	/* if (pipe(p) < 0)
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
	wait(); */
}

void	run_cmd(t_cmd_P *cmd)
{
	//int				p[2];

	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC_CMD)
		runcmd_exec(cmd);
	if (cmd->type == REDIR_CMD)
		runcmd_redir(cmd);
	if (cmd->type == PIPE_CMD)
		runcmd_pipe(cmd);
	panic ("runcmd");
	exit (1);
}
