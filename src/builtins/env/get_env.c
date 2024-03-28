/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:49:20 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 12:07:17 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_core_struct *core, char *key_to_search)
{
	t_env_list	*env_list;

	if (!key_to_search)
		return (NULL);
	env_list = core->env_list;
	while (env_list)
	{
		if ((ft_strlen(env_list->name) == ft_strlen(key_to_search))
			&& (ft_strcmp(env_list->name, key_to_search) == 0))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
