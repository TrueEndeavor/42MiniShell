/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:12:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 12:05:10 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env_nodes(t_env_list *node1, t_env_list *node2)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = node1->name;
	temp_value = node1->value;
	node1->name = node2->name;
	node1->value = node2->value;
	node2->name = temp_name;
	node2->value = temp_value;
}

t_env_list	*sort_env_list(t_env_list *env_list)
{
	t_env_list	*head;
	t_env_list	*current;
	t_env_list	*following;

	head = env_list;
	current = head;
	while (current != NULL)
	{
		following = current->next;
		while (following != NULL)
		{
			if (ft_strcmp(current->name, following->name) > 0)
			{
				swap_env_nodes(current, following);
			}
			following = following->next;
		}
		current = current->next;
	}
	return (head);
}
