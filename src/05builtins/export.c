/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/10 07:59:31 by lannur-s         ###   ########.fr       */
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

	i = 1;
	if (core->env_list == NULL)
		return (1);
	while (i < MAXARGS)
	{
		if (ecmd->argv[i])
			set_env(core, ecmd->argv[i]);
		i++;
	}
	return (core->exit_code);
}
