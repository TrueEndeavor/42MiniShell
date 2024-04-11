/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:32:11 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/11 14:22:46 by lannur-s         ###   ########.fr       */
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

void	run_here(t_herecmd_P *hcmd, t_core_struct *core, t_cmd_P *fcmd)
{
	pid_t		pid;
	char		*line;
	int			status;
	t_data      *data;

	pid = fork();
	if (pid == 0)
	{
		setup_heredoc_signals();
		data = simpleton();
		data->core = core;
		data->fcmd = fcmd;
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				ft_printf("warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", hcmd->delimiter);
				frhere(hcmd, core, line, fcmd);
				exit(EXIT_SUCCESS);
			}
			if (ft_strcmp(line, hcmd->delimiter) == 0)
			{
				frhere(hcmd, core, line, fcmd);
				exit(EXIT_SUCCESS);
			}
			line = ft_exh(core, &line, 0, 0);
			here_ext(line, hcmd);
		}
	}
	core->exit_code = waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		core->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		core->exit_code = process_signals_in_heredocs(status);
}

bool	handle_heredoc(t_core_struct *core, t_cmd_P *root, int j)
{
	int			i;
	t_herecmd_P	*curr;
	char		*temp;

	i = (core->ih);
	core->ih = 0;
	while (j < i)
	{
		curr = (t_herecmd_P *)core->hcmd[j];
		temp = ft_itoa(j);
		curr->filename = ft_strjoin ("tmp/heredoc_", temp);
		free(temp);
		curr->fd = open(curr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (curr->fd < 0)
		{
			printf ("heredoc fd opening failed\n");
		}
		else
		{
			run_here(curr, core, root);
			close (curr->fd);
		}
		j++;
	}
	return (check_for_exit_code(core->exit_code, SIGINT));
}
