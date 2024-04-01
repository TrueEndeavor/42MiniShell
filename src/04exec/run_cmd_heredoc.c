/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:51:48 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/31 22:51:48 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	runcmd_here(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd)
{
	t_herecmd_P	*hcmd;
	pid_t		pid;
	char		*line;
	int			fd[2];

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
	core->exit_code = wait(NULL);
	ft_printf ("core->exit_code: %d\n", core->exit_code);
	run_cmd(hcmd->cmd, core, fcmd);
}
