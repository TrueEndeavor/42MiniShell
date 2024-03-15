/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/14 13:25:47 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_execcmd_P *ecmd, t_core_struct *core)
{
	t_env_list  *current;
	t_env_list  *previous;

	current = core->env_list;
	previous = current;
	while (ft_strcmp(current->name, ecmd->argv[1]) != 0)
	{
		previous = current;
		current = current->next;
	}
	if (ft_strcmp(current->name, core->env_list->name) == 0)
	{
		core->env_list = core->env_list->next;
		free(current->name);
		free(current->value);
		current->next = NULL;
	}
	else if (current != NULL)
	{
		previous->next = current->next;
		free(current->name);
		free(current->value);
		current->next = NULL;
	}
	return (0);
}
