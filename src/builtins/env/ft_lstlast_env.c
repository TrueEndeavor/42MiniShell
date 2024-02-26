/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:10:32 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/26 17:11:41 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_lstlast_env(t_env_list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
