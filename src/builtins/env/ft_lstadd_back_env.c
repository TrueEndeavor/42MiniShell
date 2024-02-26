/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:59:56 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/26 17:13:07 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env_list **lst, t_env_list *new)
{
	if (*lst)
		ft_lstlast_env(*lst)->next = new;
	else
		*lst = new;
}
