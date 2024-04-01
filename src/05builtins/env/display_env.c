/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/31 23:14:02 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env_from_array(int count_of_env_vars, char	**envp)
{
	int	i;

	i = 0;
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
	if (env_list == NULL)
		return ;
	while (env_list)
	{
		if (is_export == 0)
		{
			if ((ft_strcmp(env_list->value, "") != 0))
				printf("%s=%s\n", env_list->name, env_list->value);
		}
		else if (is_export == 1)
		{
			if ((env_list)->value != NULL)
				printf("export %s=\"%s\"\n", env_list->name, env_list->value);
			else
				printf("export %s\n", (env_list)->name);
		}
		env_list = (env_list)->next;
	}
}
