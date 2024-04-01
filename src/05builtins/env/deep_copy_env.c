/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deep_copy_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:56 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 10:15:25 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*deep_copy_env(t_env_list *env_list)
{
	t_env_list	*new_head;
	t_env_list	*temp;
	char		*copy_name;
	char		*copy_value;
	int			i;

	i = 0;
	new_head = NULL;
	temp = env_list;
	while (temp != NULL)
	{
		copy_name = ft_strdup(temp->name);
		if (!copy_name)
		{
			ft_lstclear_env(&new_head, free);
			return (NULL);
		}
		copy_value = ft_strdup(temp->value);
		if (!copy_value)
			return (free(copy_name), NULL);
		ft_lstadd_back_env(&new_head, ft_lstnew_env(copy_name, copy_value));
		temp = temp->next;
		i++;
	}
	return (new_head);
}
