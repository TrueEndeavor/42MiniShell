/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/04 13:42:05 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_execcmd_P *ecmd, t_core_struct *core)
{
    int i;
    
    i = 1;
    
    if (ft_strcmp(ecmd->argv[i], "-n") == 0)
    {
        i++;
            while (ecmd->argv[i] != NULL)
        {
            printf("%s",ecmd->argv[i]);
            i++;
        }
    }
    else
    {
        while (ecmd->argv[i] != NULL)
        {
            printf("%s",ecmd->argv[i]);
            i++;
        }
        printf ("\n");
    }
    (void) core;
    return (0);
}