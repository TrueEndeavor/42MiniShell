/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/21 14:04:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    match_builtin(t_cmd_P *root, t_general *general)
{
	t_execcmd_P	*ecmd;

	ecmd = (t_execcmd_P *) root;
    if (ft_strcmp(ecmd->argv[0], "cd") == 0)
    {
        printf("cd\n");
    }
    if (ft_strcmp(ecmd->argv[0], "echo") == 0)
    {
        printf("echo\n");
    }
    (void) general;
    return (0);
}
