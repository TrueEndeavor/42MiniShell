/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 10:27:50 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_core_struct *core, char *key_value_pair)
{
	t_env_list	*head;
	t_env_list	*new;
	char		*key_to_set;
	char		*value_to_set;
	int			modified_flag;

	head = core->env_list;
	modified_flag = 0;
	new = NULL;
	key_to_set = get_key(key_value_pair);
	value_to_set = get_value(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");
	if (!is_valid_variable_name(key_to_set)
		|| (ft_strchr(key_to_set, '=') != NULL))
	{
		ft_printf("export: `%s': not a valid identifier\n", key_value_pair);
		core->exit_code = EXIT_FAILURE;
	}
	else
	{		
		while (core->env_list)
		{
			if ((ft_strlen((core->env_list)->name) == ft_strlen(key_to_set))
				&& (ft_strcmp((core->env_list)->name, key_to_set) == 0))
			{
				if (*value_to_set != '\0')
				{
					if (((core->env_list)->value != NULL))
						free((core->env_list)->value);
					(core->env_list)->value = ft_strdup(value_to_set);
				}
				else
				{
					if (((core->env_list)->value != NULL))
						free((core->env_list)->value);
					(core->env_list)->value = "";
				}
				modified_flag = 1;
			}
			core->env_list = (core->env_list)->next;
		}
		if (!value_to_set && modified_flag == 0)
		{
			core->env_list = head;
			new = ft_lstnew_env(key_to_set, NULL);
			if (!new)
				ft_lstclear_env(&core->env_list, free);
			ft_lstadd_back_env(&core->env_list, new);
		}
		else if (modified_flag == 0)
		{
			core->env_list = head;
			new = ft_lstnew_env(key_to_set, value_to_set);
			if (!new)
				ft_lstclear_env(&core->env_list, free);
			ft_lstadd_back_env(&core->env_list, new);
		}
	}
	core->env_list = head;
}
