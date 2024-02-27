/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 16:19:46 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* void	set_variable(int count, char	**envp)
{

} */

int	builtin_export(t_execcmd_P *ecmd, t_core_struct *core)
{
    int count;
    int i;
    char	**new_envp;    
   char *result;
   
    i = 1;
    result = NULL;    
    count = 0;
    if (core->env_list == NULL)
    {
        return (1);
    }
     printf("ecmd->argv[%d]=%s\n", i, ecmd->argv[i]);
    if (ecmd->argv[i] == NULL)
    {
        count = count_of_env_list(core->env_list);
        printf("count ====%d\n", count);
        new_envp = convert_env_to_stringarray(core->env_list);
        ft_sort_params(count, new_envp);
        display_env(count, new_envp);
    }
    while (ecmd->argv[i] && i < 10)
	{
        set_env(core->env_list, ecmd->argv[i]);
        display_env_from_list(&core->env_list);
	   i++;
    }
    return (0);
}


