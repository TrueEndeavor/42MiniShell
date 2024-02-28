/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/28 11:41:51 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    match_builtin(t_cmd_P *root, t_core_struct *core)
{
	t_execcmd_P	*ecmd;

	ecmd = (t_execcmd_P *) root;
    if (ft_strcmp(ecmd->argv[0], "env") == 0)
    {
        printf("matched builtin = env\n");
        builtin_env(ecmd, core);        
        return (1);        
    }
    if (ft_strcmp(ecmd->argv[0], "export") == 0)
    {
        printf("matched builtin = export\n");
        builtin_export(ecmd, core);
        return (1);        
    } 
    if (ft_strcmp(ecmd->argv[0], "unset") == 0)
    {
        printf("matched builtin = unset\n");
        //builtin_unset(ecmd, core);
        return (1);        
    } 
    if (ft_strcmp(ecmd->argv[0], "echo") == 0)
    {
        printf("matched builtin = echo\n");
        builtin_echo(ecmd, core);
        return (1);        
    }
    if (ft_strcmp(ecmd->argv[0], "cd") == 0)
    {
        printf("matched builtin = cd\n");
        //builtin_cd(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
    {
        printf("matched builtin = pwd\n");
        //builtin_pwd(ecmd, core);
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "exit") == 0)
    {
        printf("matched builtin = exit\n");
        return (1);
    }
    (void) core;
    return (0);
}
