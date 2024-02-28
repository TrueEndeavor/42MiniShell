/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/28 14:07:44 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_with_no_name(t_env_list *env_list)
{
	int			count;
	char		**new_envp;
	
	count = ft_lstsize_env(env_list);
	new_envp = convert_env_to_stringarray(env_list);
	sort_env_list(env_list);
	display_env_from_list(env_list, 1);
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
		env_list_copy = deep_copy_env(core->env_list);;
		printf("address orig = %p\n", core->env_list);
		printf("address copy = %p\n", env_list_copy);
		export_with_no_name(env_list_copy);
		return (0);
	}
	while (ecmd->argv[i] && i < 10)
	{
		set_env(core, ecmd->argv[i]);
		display_env_from_list(core->env_list, 1);
		i++;
	}
	return (0);
}


