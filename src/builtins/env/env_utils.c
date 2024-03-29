/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/29 09:48:31 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_env_to_stringarray(t_env_list *env_list)
{
	char	*temp_envp;
	char	**new_envp;
	int		i;

	i = 0;
	temp_envp = NULL;
	if (!env_list)
		return (NULL);
	new_envp = ft_calloc(sizeof(char *), ft_lstsize_env(env_list) + 1);
	if (!new_envp)
		return (NULL);
	while (env_list)
	{
		if (env_list->value == NULL)
		{
			new_envp[i] = ft_strdup(env_list->name);
		}
		else
		{
			temp_envp = ft_strjoin(env_list->name, "=");
			if (!temp_envp)
				return (NULL);
			new_envp[i] = ft_strjoin(temp_envp, env_list->value);
			free(temp_envp);
			if (!new_envp[i])
				return (NULL);
		}
		i++;
		env_list = env_list->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	*get_key(char *s)
{
	char	*result;

	result = ft_strchr(s, '=');
	if (result)
		return (ft_substr(s, 0, (ft_strlen(s) - ft_strlen(result))));
	else
		return (s);
}

char	*get_value(char *s)
{
	char	*found_key_at;
	char	*result;
	int		start_index;

	found_key_at = ft_strchr(s, '=');
	result = NULL;
	if (found_key_at)
	{
		start_index = (ft_strlen(s) - ft_strlen(found_key_at)) + 1;
		result = ft_substr(s, start_index, ft_strlen(s));
	}
	else
	{
		result = ft_calloc(1, sizeof(char));
		if (!result)
			return (NULL);
		*result = '\0';
	}
	return (result);
}

t_env_list	*init_env(char **envp)
{
	t_env_list	*minishell_envp_head;
	t_env_list	*new;
	int			i;

	if (!envp || !*envp)
	{
		new = ft_lstnew_env("PWD", getenv("PWD"));
		if (!new)
			return ((ft_lstclear_env(&minishell_envp_head, free), NULL));
		ft_lstadd_back_env(&minishell_envp_head, new);
		return (minishell_envp_head);
	}
	minishell_envp_head = NULL;
	i = 0;
	while (envp[i])
	{
		if ((ft_strchr(envp[i], '=')) != NULL)
		{
			new = ft_lstnew_env(get_key(envp[i]), get_value(envp[i]));
			if (!new)
				return ((ft_lstclear_env(&minishell_envp_head, free), NULL));
			ft_lstadd_back_env(&minishell_envp_head, new);
		}
		i++;
	}
	return (minishell_envp_head);
}
