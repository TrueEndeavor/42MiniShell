/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:24:46 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/28 13:26:24 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*create_dummy_env(void)
{	
	char	*name;
	char	*value;

	name = ft_strdup("creators");
	if (!name)
		return (NULL);
	value = ft_strdup("Latha and Rico");
	if (!value)
	{
		free (name);
		return (NULL);
	}
	return (ft_lstnew_env(name, value));
}
