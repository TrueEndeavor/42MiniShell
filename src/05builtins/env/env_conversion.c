/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:18:17 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/31 23:18:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_var_to_string(const char *name, const char *value)
{
	char	*env_str;
	char	*env_val;

	if (value == NULL)
		env_str = ft_strdup(name);
	else
	{
		env_val = ft_strjoin("=", value);
		env_str = ft_strjoin(name, env_val);
		free(env_val);
	}
	return (env_str);
}

char	**allocate_env_array(int size)
{
	return (ft_calloc(sizeof(char *), size + 1));
}

char	**convert_env_to_stringarray(t_env_list *env_list)
{
	int		size;
	int		i;
	char	**new_envp;

	if (!env_list)
		return (NULL);
	size = ft_lstsize_env(env_list);
	new_envp = allocate_env_array(size);
	if (!new_envp)
		return (NULL);
	i = 0;
	while (env_list)
	{
		new_envp[i++] = env_var_to_string(env_list->name, env_list->value);
		env_list = env_list->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
