/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:13 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/11 14:11:26 by lannur-s         ###   ########.fr       */
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
	ft_putstr_fd("heredoc> ",STDOUT_FILENO);
	*line = buffer;
	if (!readable)
		free(buffer);
	return (readable);
}

void	runcmd_exec(t_cmd_P *cmd, t_core_struct *core)
{
	t_execcmd_P	*ecmd;

	ecmd = (t_execcmd_P *) cmd;
	if (ecmd->argv[0] == 0)
		exit (1);
	printf("######RUNCMD_EXEC######\n");
	printf("THE COMMAND IS = %s\n", ecmd->argv[0]);
	ft_execute(ecmd->argv, convert_env_to_stringarray(core->env_list));
	//exit(g_exit_code);
}

void	runcmd_redir(t_cmd_P *cmd, t_core_struct *core)
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
 */	run_cmd(rcmd->cmd, core);
}

void	runcmd_pipe(t_cmd_P *cmd, t_core_struct *core)
{
	printf("++++++++++++++++runcmd_pipe\n");
	t_pipecmd_P	*pcmd;
	int p[2];
	int status;
	int l_child;
	int r_child;
	int last_status;
	
	pcmd = (t_pipecmd_P *)cmd;
	if (pipe(p) < 0)
		panic("pipe");
	l_child = fork1();
	if (l_child == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		close(p[1]);
		run_cmd(pcmd->left, core);
	}
	else
	{
		r_child = fork1();
		if (r_child == 0)
		{
			close(0);
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			close(p[1]);
			run_cmd(pcmd->right, core);
		}
		else
		{
			close(p[0]);
			close(p[1]);
		/* 	wait(0);
			wait(0);
		 */
			while (waitpid(l_child, &status, 0) > 0 || \
				waitpid(r_child, &status, 0) > 0) 
				{
	                if (WIFEXITED(status)) {
	                    last_status = WEXITSTATUS(status);
	                }
				}
	        printf("Exit status of the last child was %d\n", last_status);
	        exit(last_status);
		}
	}

}


void	runcmd_here(t_cmd_P *cmd, t_core_struct *core)
{
	t_herecmd_P *hcmd;
	pid_t		pid;
	char		*line;
	int			fd[2];
	//int status;

	hcmd = (t_herecmd_P *) cmd;
	if (pipe(fd) == -1)
		panic("pipe for heredoc broke, pls fix");
	ft_putstr_fd("heredoc> ",STDOUT_FILENO);
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
	g_exit_code = wait(NULL);
	printf ("g_exit_code: %d\n", g_exit_code);
	//waitpid(-1, &status, )
	run_cmd(hcmd->cmd, core);
}

void	run_cmd(t_cmd_P *cmd, t_core_struct *core)
{
	//int				p[2];
	int status;
	int child_pid;
	int last_status;

	
	if (cmd == 0)
		exit (1);
	if (cmd->type == EXEC_CMD)
	{
		child_pid = fork1();
		if(child_pid == 0)
		{
			// child signals
			setup_child_signals();
			runcmd_exec(cmd, core);
		}
		else 
        { 
	        last_status = waitpid(child_pid, &status, 0);
	        if (WIFEXITED(status)) 
	        {
	            last_status = WEXITSTATUS(status);
	            printf("Exit status of the child was %d\n", last_status);
	        }
	        exit(last_status);
    }
	}
	if (cmd->type == REDIR_CMD)
		runcmd_redir(cmd, core);
	if (cmd->type == PIPE_CMD)
	{
	printf("++++++++++++++++calling runcmd_pipe\n");
		runcmd_pipe(cmd, core);
	}
	if (cmd->type == HERE_CMD)
	{
		runcmd_here(cmd, core);
	}
	//else
	//	panic ("runcmd panic");
	exit (0);
}
