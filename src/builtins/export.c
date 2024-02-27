/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 22:18:56 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_execcmd_P *ecmd, t_core_struct *core)
{
    int count;
    int i;
    char	**new_envp;    
   
    i = 1;
    count = 0;
    if (core->env_list == NULL)
    {
        return (1);
    }
     printf("ecmd->argv[%d]=%s\n", i, ecmd->argv[i]);
    if (ecmd->argv[i] == NULL)
    {
printf("address export with noname %p\n", &core->env_list);      
        count = ft_lstsize_env(core->env_list);
        printf("count ====%d\n", count);
        new_envp = convert_env_to_stringarray(core->env_list);
        ft_sort_params(count, new_envp);
        display_env(count, new_envp);
    }
    while (ecmd->argv[i] && i < 10)
	{
printf("address of el in set %p\n", &core->env_list);          
        set_env(core, ecmd->argv[i]);
        //display_env_from_list(&core->env_list);
	   i++;
    }
    return (0);
}


