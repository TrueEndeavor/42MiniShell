/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:52:44 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/20 10:30:04 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	min_int(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	is_valid_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_valid_variable_name(char *name)
{
	int		i;
	int		len;
	
	i = 0;
	len = ft_strlen(name);
	if (!is_valid_variable_char(name[i]))
		return (false);
	i++;
	while (name[i] != '\0' || i < len)
	{
		if (!is_valid_variable_char(name[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_update_SHLVL(t_core_struct *core)
{
	int i;
	t_env_list *node;

	node = get_node(core, "SHLVL");
	i = ft_atoi(node->value);
	i++;
	free(node->value);
	node->value = ft_itoa(i);
}
