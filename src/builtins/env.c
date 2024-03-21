/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:45:19 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/21 05:32:06 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_execcmd_P *ecmd, t_core_struct *core)
{
	int arg_count;
	int i;

	i = 1;
	arg_count = 0;
	core->exit_code = EXIT_SUCCESS;
	if (core->env_list == NULL)
	{
		printf("no env...\n");
		core->exit_code = EXIT_FAILURE;
		return (core->exit_code);
	}
    while (ecmd->argv[i] != NULL)
	{
        if (ft_strcmp(ecmd->argv[i], "env") != 0) 
			arg_count++;
		i++;
    }		
	if (arg_count >= 1) 
	{
		ft_printf("env: ʻ%s’: No such file or directory", ecmd->argv[1]);
		core->exit_code = 127;
		return (core->exit_code);
	}
	else
		display_env_from_list(core->env_list, 0);
	return (core->exit_code);
}
