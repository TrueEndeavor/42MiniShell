/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/10 09:26:03 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_key(t_core_struct *core, char *key_to_set, char *key_value_pair)
{
	int	ret;

	ret = 0;
	if (!key_to_set)
		panic ("key to set not found");
	if (!is_valid_variable_name(key_to_set)
		|| (ft_strchr(key_to_set, '=') != NULL))
	{
		ft_printf("export: `%s': not a valid identifier\n", key_value_pair);
		core->exit_code = EXIT_FAILURE;
		ret = 1;
	}
	return (ret);
}

void	replace_val(char **val, char *value_to_set)
{
	if (*val != NULL)
		free(*val);
	*val = ft_strdup(value_to_set);
}

void	add_enventry(char *key, char *value, int mod_flag, t_env_list *head)
{
	t_env_list	*new;

	new = NULL;
	if (value != NULL && mod_flag == 0)
	{
		new = ft_lstnew_env(key, value);
		if (!new)
			ft_lstclear_env(&head, free);
		ft_lstadd_back_env(&head, new);
	}
	else if (mod_flag == 0)
	{
		new = ft_lstnew_env(key, NULL);
		if (!new)
			ft_lstclear_env(&head, free);
		ft_lstadd_back_env(&head, new);
	}
}

void	replace_enventry(t_env_list **node, char *key, char *value, int *mod_flag)
{
	if ((ft_strlen((*node)->name) == ft_strlen(key)) && \
		(ft_strcmp((*node)->name, key) == 0))
	{
		if (*value != '\0')
			replace_val(&(*node)->value, value);
		else
			replace_val(&(*node)->value, "");
		*mod_flag = 1;
	}
}

void	set_env(t_core_struct *core, char *key_value_pair)
{
	t_env_list	*head;
	char		*key_to_set;
	char		*value_to_set;
	int			modified_flag;

	head = core->env_list;
	modified_flag = 0;
	key_to_set = get_key(key_value_pair);
	value_to_set = ft_strtrim(get_value(key_value_pair), " ");
	if (validate_key(core, key_to_set, key_value_pair) == 1)
		return ;
	while (core->env_list)
	{
		replace_enventry((&(core->env_list)), \
				key_to_set, value_to_set, &modified_flag);
		core->env_list = (core->env_list)->next;
	}
	add_enventry(key_to_set, value_to_set, modified_flag, head);
	core->env_list = head;
}
