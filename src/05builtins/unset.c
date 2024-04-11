/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 12:22:33 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_one(t_core_struct *core, t_env_list *cur, t_env_list *prev)
{
	if (cur != NULL && ft_strcmp(cur->name, core->env_list->name) == 0)
	{
		core->env_list = core->env_list->next;
		free(cur->name);
		free(cur->value);
		cur->next = NULL;
		free(cur);
	}
	else if (cur != NULL)
	{
		prev->next = cur->next;
		free(cur->name);
		free(cur->value);
		cur->next = NULL;
		free(cur);
	}
}

int	builtin_unset(t_execcmd_P *ecmd, t_core_struct *core)
{
	t_env_list	*current;
	t_env_list	*previous;
	int			i;

	i = 1;
	if (ecmd->argv[i] == NULL && ecmd->argv[i + 1] == NULL)
	{
		core->exit_code = EXIT_SUCCESS;
		return (core->exit_code);
	}
	if (ecmd->argv[i] != NULL && ecmd->argv[1][0] == '-')
	{
		ft_printf(" invalid option\n");
		core->exit_code = 2;
		return (core->exit_code);
	}
	while (ecmd->argv[i] != NULL || ecmd->argv[i + 1] != NULL)
	{
		current = get_node(core, ecmd->argv[i]);
		previous = get_previous_node(core, ecmd->argv[i]);
		if (current != NULL)
			core->exit_code = EXIT_SUCCESS;
		unset_one(core, current, previous);
		i++;
	}
	return (core->exit_code);
}
