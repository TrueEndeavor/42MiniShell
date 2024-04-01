/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:44:39 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/21 10:21:54 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assignment_word(char *str)
{
	char	*position;
	int		len;
	int		index;

	index = 0;
	position = ft_strrchr(str, '=');
	if (position)
		index = position - str;
	len = strlen(str);
	if (index == (len - 1))
		return (true);
	return (false);
}

/*
In ft_fill_exec

cmd->argv[(*argc)] = (*core->token_head)->value;
to be changed to
add_to_argv(ecmd, (*core->token_head)->value);
*/

/*
void	add_to_argv(t_execcmd_P *ecmd, char *arg)
{
	char	**new_argv;
	int	i;

	i = 0;
	ecmd->argc++;
	new_argv = malloc(cmd->argc * sizeof(char *));
	if (new_argv == NULL)
			return (NULL);
	while (i < ecmd->argc - 1)
	{
			new_argv[i] = cmd->argv[i];
			i++;
	}
	new_argv[argc - 1] = ft_strdup(arg);
	free(ecmd->argv);
	ecmd->argv = new_argv;
}
*/

/*
void free_argv(t_execcmd_P *ecmd)
{
		int	i;

		i = 0;
		while (i < ecmd->argc)
		{
				free(ecmd->argv[i]);
		}
		free(ecmd->argv);
		free(ecmd);
}
*/
