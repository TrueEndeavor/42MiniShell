/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:07:20 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/26 17:14:51 by lannur-s         ###   ########.fr       */
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
