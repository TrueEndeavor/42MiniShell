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

void	fill_line(char **str, char **name, char **var, char *ret)
{
	int	i;
	int	j;
	int	i_var;

	i = 0;
	j = 0;
	i_var = 0;
	while ((*str)[j] != 0)
	{
		if ((*str)[j] == '$' && (*str)[j + 1] != ' ' && (*str)[j + 1] != '\0')
		{
			copy_variable (ret, var[i_var], i);
			i += ft_slen(var[i_var]);
			j += (ft_slen(name[i_var]));
			i_var++;
		}
		else
		{
			ret[i] = (*str)[j];
			i++;
		}
		j++;
	}
	ret[i] = '\0';
}

int	fill_tab(char **str, char **name, char **var, t_core_struct *core)
{
	int	i;
	int	i_var;
	int	var_count;

	var_count = 0;
	i_var = 0;
	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$' && (*str)[i + 1] != ' ')
		{
			name[i_var] = NULL;
			var[i_var] = NULL;
			name[i_var] = get_name(*str, i);
			i += (int)ft_strlen(name[i_var]);
			var[i_var] = dupl(get_env(core, name[i_var]));
			i_var++;
			var_count++;
		}
		i++;
	}
	return (var_count);
}

char	*ft_exh(t_core_struct *core, char **s, int var_c, int i)
{
	char	*ret;
	char	**name;
	char	**var;
	int		size;
	
	size = check_num_arg((*s));
	name = malloc(size * sizeof(char *));
	var = malloc(size * sizeof(char *));
	ft_initialize_tab(name, var, size);
	var_c = fill_tab(s, name, var, core);
	if (var_c == -1)
		return (free_quotes(s, name, var));
	size = (int)ft_strlen(*s);
	i = 0;
	while (var_c != 0)
	{
		size += ft_slen(var[i]);
		size -= (ft_slen(name[i]) + 1);
		i++;
		var_c--;
	}
	ret = malloc ((size + 1) *(sizeof(char)));
	fill_line(s, name, var, ret);
	free_quotes(s, name, var);
	return (ret);
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
	//setup_mother_signals();
	pid = fork();
	if (pid == 0)
	{
		//setup_heredoc_signals();
		close(fd[0]);
		while (ft_get_line(&line))
		{
			if (ft_strcmp(line, hcmd->delimiter) == 0)
			{
				free (line);
				close (fd[1]);
				ft_free_cmd(fcmd);
				ft_free_tok_list(core->token_head);
				ft_free_env(core->env_list);
				free(core);
				exit(EXIT_SUCCESS);
			}
			line = ft_exh(core, &line, 0, 0);
			write (fd[1], line, ft_strlen(line));
			write (fd[1], "\n", 1);
			free(line);
		}
	}
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
	close (fd[1]);
	core->exit_code = wait(NULL);
	ft_printf ("in heredocs core->exit_code: %d\n", core->exit_code);
	run_cmd(hcmd->cmd, core, fcmd);
}
