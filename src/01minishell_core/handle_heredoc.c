/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:32:11 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/05 11:18:24 by trysinsk         ###   ########.fr       */
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

	//setup_mother_signals();
	pid = fork();
	if (pid == 0)
	{
		//setup_heredoc_signals();
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, hcmd->delimiter) == 0)
			{
				free (line);
				close (hcmd->fd);
				free (hcmd->filename);
				ft_free_cmd(fcmd);
				ft_free_tok_list(core->token_head);
				ft_free_env(core->env_list);
				free(core);
				exit(EXIT_SUCCESS);
			}
			line = ft_exh(core, &line, 0, 0);
			ft_putstr_fd(line, hcmd->fd);
			ft_putstr_fd("\n", hcmd->fd);
			free(line);
		}
	}
	waitpid(pid, NULL, 0);
	core->exit_code = wait(NULL);
	ft_printf ("in heredocs core->exit_code: %d\n", core->exit_code);
}

void    handle_heredoc(t_core_struct *core, t_cmd_P *root)
{
    int             i;
	int				j;
    t_herecmd_P     *current;
    char            *temp;

    i = (core->ih);
	j = 0;
    core->ih = 0;
    while (j < i)
    {
        current = (t_herecmd_P *)core->hcmd[j];
        temp = ft_itoa(j);
        current->filename = ft_strjoin ("tmp/heredoc_", temp);
        free(temp);
        current->fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (current->fd < 0)
            printf ("heck\n");
		else
		{
        	run_here(current, core, root);
			close (current->fd);
		}
		j++;
	}
}