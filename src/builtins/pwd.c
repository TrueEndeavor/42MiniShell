/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/04 13:25:42 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_execcmd_P *ecmd, t_core_struct *core)
{
    char *buff;

    (void) ecmd;
    buff = get_env(core, "PWD");
    if (buff != NULL)
        printf ("%s\n", buff);
/*     else 
    {
        buff = getcwd(buff, 2000);
        printf ("%s\n", buff);
        free(buff);
    } */
    return (0);
}