/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:33:10 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/26 17:33:43 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_env(t_env_list *lst)
{
	int		count;

	count = 0;
	if (lst)
	{
		count++;
		while (lst->next)
		{
			count++;
			lst = lst->next;
		}
	}
	return (count);
}
