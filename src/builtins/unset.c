/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/27 10:20:09 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_execcmd_P *ecmd, t_core_struct *core)
{
	t_env_list  *current;
	t_env_list  *previous;
	int	i;

	i = 1;
	while (ecmd-> argv[i] != NULL)
	{
		current = core->env_list;
		previous = current;
		if ((ecmd->argv[i] == NULL) || (ecmd->argv[i][0] == '\0'))
			return (1);	
		while (current != NULL && ft_strcmp(current->name, ecmd->argv[i]) != 0)
		{
			previous = current;
			current = current->next;
		}
		if (current != NULL && ft_strcmp(current->name, core->env_list->name) == 0)
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
		i++;
	}
	return (0);
}
