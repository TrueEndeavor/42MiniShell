/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:51:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 10:21:34 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_env(t_env_list **lst, void (*del)(void *))
{
	t_env_list	**begin;
	t_env_list	*tmp;

	if (lst && del)
	{
		begin = lst;
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_lstdelone_env(tmp, del);
			tmp = NULL;
		}
		*begin = NULL;
	}
}
