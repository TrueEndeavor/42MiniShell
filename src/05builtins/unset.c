/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:37:31 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/04 23:52:47 by lannur-s         ###   ########.fr       */
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
	}
	else if (cur != NULL)
	{
		prev->next = cur->next;
		free(cur->name);
		free(cur->value);
		cur->next = NULL;
	}
}

int	builtin_unset(t_execcmd_P *ecmd, t_core_struct *core)
{
	t_env_list	*current;
	t_env_list	*previous;
	int			i;

	i = 1;
	if (ecmd->argv[1][0] == '-')
	{
		ft_printf(" invalid option\n");
		core->exit_code = 2;
		return (core->exit_code);
	}	
	while (ecmd->argv[i] != NULL)
	{
		if ((ecmd->argv[i] != NULL) && (!is_valid_variable_name(ecmd->argv[i])))
		{
			//ft_printf("unset: `%s': not a valid identifier\n", ecmd->argv[i]);
			core->exit_code = EXIT_SUCCESS;
			i++;
			continue ;
		}
		current = core->env_list;
		previous = current;
		if ((ecmd->argv[i] == NULL) || (ecmd->argv[i][0] == '\0'))
			return (1);
		while (current != NULL && ft_strcmp(current->name, ecmd->argv[i]) != 0)
		{
			previous = current;
			current = current->next;
		}
		unset_one(core, current, previous);
		i++;
	}
	return (core->exit_code);
}
