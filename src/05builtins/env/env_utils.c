/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/09 21:49:55 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *s)
{
	char	*result;

	result = ft_strchr(s, '=');
	if (result)
		return (ft_substr(s, 0, (ft_strlen(s) - ft_strlen(result))));
	else
		return (ft_strdup(s));
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
