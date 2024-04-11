/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:11:30 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/11 10:52:10 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return_builtin_child(t_execcmd_P *ecmd)
{
	int	i;

	i = 0;
	if (ecmd->argv[0] == NULL)
		i = 0;
	if (ft_strcmp(ecmd->argv[0], "env") == 0)
		i = 1;
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		i = 1;
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		i = 1;
	else if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		i = 1;
	else if (ft_strcmp(ecmd->argv[0], "cd") == 0)
		i = 1;
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		i = 1;
	else if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		i = 1;
	return (i);
}

int	builtin_ch(t_cmd_P *root, t_core_struct *core, t_cmd_P *f, char **en)
{
	t_execcmd_P	*ecmd;
	int			ret;

	ret = 0;
	ecmd = (t_execcmd_P *) root;
	ret = ft_return_builtin_child(ecmd);
	if (ft_strcmp(ecmd->argv[0], "env") == 0)
		core->exit_code = builtin_env(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		core->exit_code = builtin_export(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		core->exit_code = builtin_unset(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		core->exit_code = builtin_echo(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "cd") == 0)
		core->exit_code = builtin_cd(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		core->exit_code = builtin_pwd(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		exit_ch(ecmd, core, f, en);
	return (ret);
}
