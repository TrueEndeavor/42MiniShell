/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 07:31:38 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 09:33:41 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	runleft(t_pipecmd_P *pcmd, int p[], t_core_struct *core, t_cmd_P *fcmd)
{
	close(1);
	dup(p[1]);
	close(p[0]);
	close(p[1]);
	run_cmd(pcmd->left, core, fcmd);
}

void	runright(t_pipecmd_P *pcmd, int p[], t_core_struct *core, t_cmd_P *fcmd)
{
	close(0);
	dup(p[0]);
	close(p[0]);
	close(p[1]);
	run_cmd(pcmd->right, core, fcmd);
}

void	wait_for_child_processes(int l_child, int r_child, int *last_status)
{
	int	status;

	while (waitpid(l_child, &status, 0) > 0 || \
				waitpid(r_child, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
	}
}

int	execute_pipe_command(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_pipecmd_P		*pcmd;
	int				p[2];
	int				last_status;
	pid_t			l_child;
	pid_t			r_child;

	last_status = 0;
	pcmd = (t_pipecmd_P *)cmd;
	if (pipe(p) < 0)
		panic("pipe");
	l_child = fork1();
	if (l_child == 0)
		runleft(pcmd, p, core, fcmd);
	else
	{
		r_child = fork1();
		if (r_child == 0)
			runright(pcmd, p, core, fcmd);
		else
		{
			close_pipe(p);
			wait_for_child_processes(l_child, r_child, &last_status);
		}
	}
	return (last_status);
}

int	runcmd_pipe(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	int			last_status;

	last_status = 0;
	last_status = execute_pipe_command(cmd, core, fcmd);
	ft_free_cmd(fcmd);
	ft_free_tok_list(core->token_head);
	ft_free_env(core->env_list);
	free(core);
	exit(last_status);
}
