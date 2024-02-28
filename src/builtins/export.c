/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/28 18:57:07 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_with_no_name(t_env_list *env_list)
{
	
	display_env_from_list(sort_env_list(env_list), 1);
}

int	builtin_export(t_execcmd_P *ecmd, t_core_struct *core)
{
	int			i;
	t_env_list	*env_list_copy;

	i = 1;
	if (core->env_list == NULL)
		return (1);
	if (ecmd->argv[1] == NULL)
	{
		env_list_copy = deep_copy_env(core->env_list);
		export_with_no_name(env_list_copy);
		free (env_list_copy);
		return (0);
	}
	while (ecmd->argv[i] && i < 10)
	{
		set_env(core, ecmd->argv[i]);
		i++;
	}
	printf("address of env_list in ----end of set %p\n", core->env_list);		
		env_list_copy = deep_copy_env(core->env_list);
	printf("address of env_list_copy in ----end of set %p\n", env_list_copy);			
		display_env_from_list(sort_env_list(env_list_copy), 1);
	return (0);
}


