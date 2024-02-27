/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 10:35:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_core_struct *core, char *key_value_pair)
{
	//t_env_list	*env_list;
	//int	len;
	char    *key_to_set;
	char    *value_to_set;

    key_to_set = getKey(key_value_pair);
    value_to_set = getValue(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");
	printf("key_to_set = %s\n",key_to_set);
	printf("value_to_set = %s\n",value_to_set);	
	printf("existing_value = %s\n", get_env(core, key_to_set));

}