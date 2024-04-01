/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:10:26 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/28 10:23:11 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*get_node(t_core_struct *core, char *key_to_search)
{
	t_env_list	*env_list;

	if (!key_to_search)
		return (NULL);
	env_list = core->env_list;
	while (env_list)
	{
		if ((ft_strlen(env_list->name) == ft_strlen(key_to_search))
			&& (ft_strcmp(env_list->name, key_to_search) == 0))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
