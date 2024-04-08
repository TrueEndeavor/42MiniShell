/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:13 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 13:28:55 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void runcmd_here(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_herecmd_P		*hcmd;
	int				fd;

	hcmd = (t_herecmd_P *)cmd;
	fd = open (hcmd->filename, O_RDONLY, 0777);
	if (fd == -1)
		ft_printf ("oof\n");
	dup2 (fd, STDIN_FILENO);
	close (fd);
	unlink (hcmd->filename);
	free(hcmd->filename);
	run_cmd(hcmd->cmd, core, fcmd);
}

int	runcmd_exec(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_execcmd_P	*ecmd;
	char		**env_array;
	int			i;

	env_array = NULL;
	ecmd = (t_execcmd_P *) cmd;
	if (ecmd->argv[0] == 0)
		exit (1);
	env_array = convert_env_to_stringarray(core->env_list);
	#if DEBUG
	dprintf(2, "######RUNCMD_EXEC######\n");
	dprintf(2, "THE COMMAND IS = %s\n", ecmd->argv[0]);
	dprintf(2, "\033[0;36m######OUTPUT######\n\033[0m");
	#endif
	if (!match_builtin(cmd, core, NULL))
	{
		core->exit_code = ft_execute(ecmd->argv, env_array);
	}
	i = core->exit_code;
	ft_free_cmd(fcmd);
	ft_free_tok_list(core->token_head);
	ft_free_env(core->env_list);
	free(core);
	ft_free(NULL, env_array);
	exit(i);
}

void	runcmd_redir(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_redircmd_P	*rcmd;
	int fd;
	
	rcmd = (t_redircmd_P *) cmd;
	fd = open(rcmd->file, rcmd->mode, rcmd->permission);
	if (fd < 0)
	{
		perror(rcmd->file);
		ft_free_cmd(fcmd);
		ft_free_tok_list(core->token_head);
		ft_free_env(core->env_list);
		free(core);
		exit(1);
	}
	dup2(fd, rcmd->fd);
	close (fd);
	run_cmd(rcmd->cmd, core, fcmd);
}

void	run_cmd(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC_CMD)
	{
		runcmd_exec(cmd, core, fcmd);
	}
	if (cmd->type == REDIR_CMD)
		runcmd_redir(cmd, core, fcmd);
	if (cmd->type == PIPE_CMD)
	{
		core->exit_code = runcmd_pipe(cmd, core, fcmd);
	}
	if (cmd->type == HERE_CMD)
	{
		runcmd_here(cmd, core, fcmd);
	}
}
