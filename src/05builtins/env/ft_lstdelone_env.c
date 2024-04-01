/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:07:20 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 10:48:15 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_env(t_env_list *lst, void (*del)(void *))
{
	if (lst != NULL && del)
	{
		del(&lst->name);
		del(&lst->value);
		free(lst);
	}
}
