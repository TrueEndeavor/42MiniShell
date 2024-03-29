/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/29 09:45:33 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env5(t_core_struct *core, char *key_to_set)
{
	int	ret;

	ret = 0;
	if (!key_to_set)
		panic ("key to set not found");
	printf ("............key_to_set = %s\n", key_to_set);
	if (!is_valid_variable_name(key_to_set)
		|| (ft_strchr(key_to_set, '=') != NULL))
	{
		ft_printf("export: `%s': not a valid identifier\n", key_to_set);
		core->exit_code = EXIT_FAILURE;
		ret = 1;
	}
	return (ret);
}

void	set_env4(t_core_struct *co, char *key, char *value, t_env_list *n)
{
	n = ft_lstnew_env(key, value);
	if (!n)
		ft_lstclear_env(&co->env_list, free);
	ft_lstadd_back_env(&co->env_list, n);
}

void	set_env3(t_core_struct *co, char *key, t_env_list *h, t_env_list *n)
{
	co->env_list = h;
	n = ft_lstnew_env(key, NULL);
	printf("adding the new variable with empty value\n");
	if (!n)
		ft_lstclear_env(&co->env_list, free);
	ft_lstadd_back_env(&co->env_list, n);
}

void	set_env2(t_core_struct *core, char *key, char *value, int *flag)
{
	while (core->env_list)
	{
		if ((ft_strlen((core->env_list)->name) == ft_strlen(key))
			&& (ft_strcmp((core->env_list)->name, key) == 0))
		{
			if (*value != '\0')
			{
				if (((core->env_list)->value != NULL))
					free((core->env_list)->value);
				(core->env_list)->value = ft_strdup(value);
			}
			else
			{
				printf("dsssssssssss............\n");
				if (((core->env_list)->value != NULL))
					free((core->env_list)->value);
				(core->env_list)->value = "";
			}
			/*if (!(core->env_list)->value)
				panic ("env list value empty");*/
			(*flag) = 1;
		}
		core->env_list = (core->env_list)->next;
	}
	printf ("value_set = %s & flag = %d \n", value, (*flag));
}

void	set_env(t_core_struct *core, char *key_value_pair)
{
	t_env_list	*head;
	t_env_list	*new;
	char		*key_to_set;
	char		*value_to_set;
	int			modified_flag;

	head = core->env_list;
	//printf("address of el in ----set %p\n", core->env_list);
	modified_flag = 0;
	new = NULL;
	key_to_set = get_key(key_value_pair);
	value_to_set = get_value(key_value_pair);
	if (set_env5(core, key_to_set) == 0)
	{
		set_env2(core, key_to_set, value_to_set, &modified_flag);
		if (!value_to_set && modified_flag == 0)
			set_env3(core, key_to_set, head, new);
		else if (modified_flag == 0)
		{
			core->env_list = head;
			set_env4(core, key_to_set, value_to_set, new);
		}
	}
	core->env_list = head;
}
