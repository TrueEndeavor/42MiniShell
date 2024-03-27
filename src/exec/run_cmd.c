/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:13 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/27 12:32:39 by trysinsk         ###   ########.fr       */
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

int	ft_get_line(char **line)
{
	char	*buffer;
	char	c;
	int		i;
	int		readable;

	i = 0;
	readable = 0;
	buffer = (char *) malloc (200 * sizeof(char));
	if (!buffer)
		return (-1);
	readable = read(0, &c, 1);
	while (readable && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		readable = read(0, &c, 1);
	}
	buffer[i] = '\0';
	ft_printf("heredoc> ");
	*line = buffer;
	if (!readable)
		free(buffer);
	return (readable);
}

int	runcmd_exec(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_execcmd_P	*ecmd;
	char		**env_array;

	env_array = NULL;
	ecmd = (t_execcmd_P *) cmd;
	if (ecmd->argv[0] == 0)
		exit (1);
	env_array = convert_env_to_stringarray(core->env_list);
	dprintf(2, "######RUNCMD_EXEC######\n");
	dprintf(2, "THE COMMAND IS = %s\n", ecmd->argv[0]);
	dprintf(2, "\033[0;36m######OUTPUT######\n\033[0m");
	core->exit_code = ft_execute(ecmd->argv, env_array);
	dprintf(2, "freeing cmd in child\n");
	ft_free_cmd(fcmd);
	dprintf(2, "freeing tok list in child\n");
	ft_free_tok_list(core->token_head);
	dprintf(2, "freeing env_list in child\n");
	ft_free_env(core->env_list);
	dprintf(2, "freeing core in child\n");
	free(core);
	dprintf(2, "freeing env** in child\n");
	ft_free(NULL, env_array);
	dprintf(2, "done\n");
	exit(core->exit_code);
}

void	runcmd_redir(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
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
 */	
    run_cmd(rcmd->cmd, core, fcmd);
}

int	runcmd_pipe(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_pipecmd_P	*pcmd;
	int p[2];
	int status;
	int l_child;
	int r_child;
	int last_status;
	
	last_status = 0;
	pcmd = (t_pipecmd_P *)cmd;
	if (pipe(p) < 0)
		panic("pipe");
	l_child = fork1();
	if (l_child == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->left, core, fcmd);
	}
	else
	{
		r_child = fork1();
		if (r_child == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			run_cmd(pcmd->right, core, fcmd);
		}
	
		else
		{
			close(p[0]);
			close(p[1]);
/* 			wait(0);
			wait(0);
		} */
		
 			while (waitpid(l_child, &status, 0) > 0 || \
				waitpid(r_child, &status, 0) > 0) 
				{
	                if (WIFEXITED(status)) {
	                    last_status = WEXITSTATUS(status);
	                }
				}
	        printf("Exit status of the last child was %d\n", last_status);
		} 
	}
		dprintf(2, "freeing cmd in pipe\n");
		ft_free_cmd(fcmd);
		dprintf(2, "freeing tok list in pipe\n");
		ft_free_tok_list(core->token_head);
		dprintf(2, "freeing env_list in pipe\n");
		ft_free_env(core->env_list);
		dprintf(2, "freeing core in pipe\n");
		free(core);
		dprintf(2, "done\n");
	    exit(last_status);
}

void	runcmd_here(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_herecmd_P *hcmd;
	pid_t		pid;
	char		*line;
	int			fd[2];
	//int status;

	hcmd = (t_herecmd_P *) cmd;
	if (pipe(fd) == -1)
		panic("pipe for heredoc broke, pls fix");
	ft_printf("heredoc> ");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (ft_get_line(&line))
		{
			if (ft_strcmp(line, hcmd->delimiter) == 0)
			{
				free (line);
				close (fd[1]);
				exit(EXIT_SUCCESS);
			}
			write (fd[1], line, ft_strlen(line));
			write (fd[1], "\n", 1);
			free(line);
		}
	}
	dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
	close (fd[1]);
	//wait(NULL);
	core->exit_code = wait(NULL);
	printf ("core->exit_code: %d\n", core->exit_code);
	run_cmd(hcmd->cmd, core, fcmd);
}

void	run_cmd(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	//int				p[2];
/* 	int status;
	int child_pid;
	int last_status; */

	
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
	//else
	//	panic ("runcmd panic");
	//exit (0);
	
}
