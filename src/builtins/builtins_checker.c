/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/20 22:36:33 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    match_builtin(t_cmd_P *root, t_core_struct *core, char *prompt)
{
	t_execcmd_P	*ecmd;

	ecmd = (t_execcmd_P *) root;
	dprintf(2, "\033[0;36m######OUTPUT######\n\033[0m");
    if (ft_strcmp(ecmd->argv[0], "env") == 0)
    {
        printf("..............ecmd->argv[1]=%s",ecmd->argv[1]);
        builtin_env(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "export") == 0)
    {
        builtin_export(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "unset") == 0)
    {
        builtin_unset(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "echo") == 0)
    {
        builtin_echo(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "cd") == 0)
    {
        builtin_cd(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
    {
        builtin_pwd(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "exit") == 0)
    {
        builtin_exit(ecmd, core, prompt);
        return (1);
    }
    (void) core;
    return (0);
}
