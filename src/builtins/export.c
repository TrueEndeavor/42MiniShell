/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/22 19:38:44 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_of_env(char **envp)
{
    int		count;
    
    count =0;
	while (*envp != NULL)
	{
	    if (*envp[0] != '\0')
		    count++;
		envp++;
    }
    return (count);
}

void	display_sorted_env(int count, char	**envp)
{
    int i;
    
    i = 1;
	while (i < count)
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

char    **make_copy_env(int count, char **envp)
{
    char	**new_envp;
    int     i;

    new_envp = malloc(sizeof(char *) * count + 1);
    if (!new_envp)  
        return (NULL);
    i = 0;
    while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
		    free(new_envp);
		    return (NULL);
        }
		i++;
	}
	new_envp[i] = NULL;
    return (new_envp);
}

/* void	set_variable(int count, char	**envp)
{

} */

int	export_builtin(t_execcmd_P *ecmd, t_core_struct *core)
{
    int count;
    int i;
    char	**new_envp;    
    
    i = 1;
    count = 0;
    printf("coucou\n");
    if (ecmd->argv[i] == NULL)
    {
        count = count_of_env(core->envp);
        new_envp = make_copy_env(count, core->envp);
        ft_sort_params(count, new_envp);
        display_sorted_env(count, new_envp);
    }
    while (ecmd->argv[i] && i < 10)
	{
	    printf("ecmd->argv[%d]=%s\n", i, ecmd->argv[i]);
	   //set_variable(ecmd->argv, core);
	   i++;
    }
    return (0);
}

