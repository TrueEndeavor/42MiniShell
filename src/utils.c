/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:52:44 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/12 11:57:00 by trysinsk         ###   ########.fr       */
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

void	ft_update_SHLVL(t_core_struct *core)
{
	int i;
	t_env_list *node;

	node = get_node(core, "SHLVL");
	printf ("SHLVL->value before: %s\n", node->value);
	i = ft_atoi(node->value);
	printf ("i before incrementing: %d\n", i);
	i++;
	printf ("i after incrementing: %d\n", i);
	free(node->value);
	node->value = ft_itoa(i);
	printf ("SHLVL->value after: %s\n", node->value);
}