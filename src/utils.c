/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:52:44 by lannur-s          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/20 10:30:04 by lannur-s         ###   ########.fr       */
=======
/*   Updated: 2024/03/20 13:38:14 by trysinsk         ###   ########.fr       */
>>>>>>> 662a541cd6ebe7e8a3c6e4540afc141e5f61e695
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

void	ft_update_shlvl(t_core_struct *core)
{
	int			i;
	t_env_list	*node;

	node = get_node(core, "SHLVL");
	i = ft_atoi(node->value);
	i++;
	free(node->value);
	node->value = ft_itoa(i);
}
