/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 10:40:14 by trysinsk         ###   ########.fr       */
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
			{
				//TODO:free all new_envp[i] so far
				//and new_envp itself at the end
				return (NULL);
			}
			new_envp[i] = ft_strjoin(temp_envp, env_list->value);
			free(temp_envp);
			if (!new_envp[i])
			{
				//TODO:free all new_envp[i] so far
				//and new_envp itself at the end
				return (NULL);
			}
		}
		i++;
		env_list = env_list->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
// function to free_env_array

char	*getKey(char *s)
{
	char	*result;

	result = ft_strchr(s, '=');
	//TODO:declare variable for the return, free it later
	if (result)
		return (ft_substr(s, 0, (ft_strlen(s) - ft_strlen(result))));
	else
		return (s);
}

char	*getValue(char *s)
{
	char	*found_key_at;
	char	*result;

	found_key_at = ft_strchr(s, '=');
	result = NULL;
	if (found_key_at)
	{
		result = ft_substr(s, (ft_strlen(s) - ft_strlen(found_key_at)) + 1, ft_strlen(s));
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
			//if (!getKey(envp[i]) || !getValue(envp[i]))
			//	return ((ft_lstclear_env(&minishell_envp_head, free), NULL));
			new = ft_lstnew_env(getKey(envp[i]), getValue(envp[i]));
			if (!new)
				return ((ft_lstclear_env(&minishell_envp_head, free), NULL));
			ft_lstadd_back_env(&minishell_envp_head, new);
		}
		i++;
	}
	return (minishell_envp_head);
}

void	display_env_from_array(int count_of_env_vars, char	**envp)
{
	int	i;

	i = 0;
		// TODO: print a new line or just ""..
	if (envp == NULL)
	{
		printf("\n");
	}
	while (i < count_of_env_vars)
	{
		if (envp[i] != NULL && (ft_strchr(envp[i], '=')) != NULL)
			if (envp[i] != NULL)
				printf ("%s\n", envp[i]);
		i++;
	}
}

void	display_env_from_list(t_env_list *env_list, int is_export)
{
	// TODO:think about return ;
	if (env_list == NULL)
		return ;
	while (env_list)
	{
		if (is_export == 0)
		{
			if ((ft_strcmp(env_list->value, "") != 0))
				printf("%s=%s\n", (env_list)->name, (env_list)->value);
		}
		if (is_export == 1)
		{
			if ((env_list)->value != NULL)
				printf("declare -x %s=\"%s\"\n", (env_list)->name, (env_list)->value);
			else
				printf("declare -x %s\n", (env_list)->name);
		}
		env_list = (env_list)->next;
	}
}
