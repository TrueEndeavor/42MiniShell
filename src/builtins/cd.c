/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/19 11:58:40 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_execcmd_P *ecmd, t_core_struct *core)
{
    t_env_list      *old_pwd;
    t_env_list      *pwd;
    
    if (ecmd->argv [2] != NULL)
        {
            printf ("too many arg\n");
            return (1);
        }
    old_pwd = get_node(core, "OLDPWD");
    pwd = get_node(core, "PWD");
    if (ecmd->argv[1] == NULL)
        chdir(get_env(core, "HOME"));
    else if (ft_strcmp(ecmd->argv[1], "-") == 0)
    {
        if (chdir (old_pwd->value) == -1)
        {
            printf ("return to old pwd failed\n");
            return (1);
        }
    }
    else if (chdir (ecmd->argv[1]) == -1)
    {
        printf ("directory change failed\n");
        return(1);
    }
    printf ("before updating\n");
    printf ("old_pwd_value: %s\n", old_pwd->value);
    printf ("pwd_value: %s\n", pwd->value);
    free(old_pwd->value);
    old_pwd->value = ft_strdup(pwd->value);
    free(pwd->value);
    // what if the buff is allocated and some random numbers allocated
    pwd->value = getcwd(NULL, 0);
    printf ("after update\n");
    printf ("old_pwd_value: %s\n", old_pwd->value);
    printf ("pwd_value: %s\n", pwd->value);
    return (0);
}