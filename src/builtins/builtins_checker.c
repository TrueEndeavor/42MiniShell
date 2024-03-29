/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 09:43:27 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return_builtin(t_execcmd_P *ecmd)
{
	int	i;

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

int	match_builtin(t_cmd_P *root, t_core_struct *core, char *prompt)
{
	t_execcmd_P	*ecmd;
	int			verif;

	ecmd = (t_execcmd_P *) root;
	verif = ft_return_builtin(ecmd);
	dprintf(2, "\033[0;36m######OUTPUT######\n\033[0m");
	if (ft_strcmp(ecmd->argv[0], "env") == 0)
		builtin_env(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		builtin_export(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		builtin_unset(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		builtin_echo(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "cd") == 0)
		builtin_cd(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		builtin_pwd(ecmd, core);
	else if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		builtin_exit(ecmd, core, prompt);
	return (verif);
}
