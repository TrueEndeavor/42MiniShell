/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:49:20 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/26 17:51:48 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_core *core, char *key_to_search)
{
	t_env_list	*env_list;
	int	len;

	if (!key_to_search)
		return (NULL);
	len = ft_strlen(key_to_search);
	env_list = core->env_list;
	while (env_list)
	{
		if (ft_strlen(env_list->key) == key_to_search && ft_strcmp(env_list->key,
				env_list))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}