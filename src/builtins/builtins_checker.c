/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/22 19:09:26 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    match_builtin(t_cmd_P *root, t_core_struct *core)
{
	t_execcmd_P	*ecmd;

	ecmd = (t_execcmd_P *) root;
    if (ft_strcmp(ecmd->argv[0], "cd") == 0)
    {
        printf("matched builtin = cd\n");
        return (1);
    }
    if (ft_strcmp(ecmd->argv[0], "echo") == 0)
    {
        printf("matched builtin = echo\n");
        return (1);        
    }
    if (ft_strcmp(ecmd->argv[0], "export") == 0)
    {
        printf("matched builtin = export\n");
        export_builtin(ecmd, core);
        return (1);        
    } 
    (void) core;
    return (0);
}
