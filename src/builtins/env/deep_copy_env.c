/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deep_copy_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:56 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/28 19:03:23 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list *deep_copy_env(t_env_list *env_list)
{
	t_env_list	*new_head;
	t_env_list	*temp;
	char	*copy_of_name;
	char	*copy_of_value;

	new_head = NULL;
	temp = env_list;
	int i = 0;
	while (temp != NULL)
	{
		copy_of_name = ft_strdup(temp->name);
		if (!copy_of_name)
		{
			ft_lstclear_env(&new_head, free);
			return (NULL);
		}
		copy_of_value = ft_strdup(temp->value);
		if (!copy_of_value)
			return (free(copy_of_name), NULL);
		ft_lstadd_back_env(&new_head, ft_lstnew_env(copy_of_name, copy_of_value));
		temp = temp->next;
		i++;
	}
	printf("segfault checker %d\n", i);
	return (new_head);
}
