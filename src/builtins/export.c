/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/19 17:01:23 by lannur-s         ###   ########.fr       */
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
	if (!is_valid_variable_name(ecmd->argv[1]))
	{
		ft_printf("export: `%s
		': not a valid identifier\n", ecmd->argv[1]);
		core->exit_code = 1;
		return (core->exit_code);
	}
	while (ecmd->argv[1] && i < MAXARGS)
	{
		set_env(core, ecmd->argv[1]);
		i++;
	}
	env_list_copy = deep_copy_env(core->env_list);
	display_env_from_list(sort_env_list(env_list_copy), 1);
	return (0);
	
	/* Test case 1: if existing and if the expanded name is not variable name - error and exit 1
	set core->exit_code=1
	 lannur-s@bess-f4r5s5:~$ export $var=dd
	bash: export: `1212=dd': not a valid identifier
	lannur-s@bess-f4r5s5:~$ echo $?
1 */
 
}


