/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:37:07 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 11:37:44 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(t_core_struct *core, char *key_value_pair)
{
	//t_env_list	*env_list;
	//int	len;
	char    *key_to_set;
	char    *value_to_set;
	char    *existing_value;
	
	printf("key_value_pair = %s\n",key_value_pair);
    key_to_set = getKey(key_value_pair);
	printf("key_to_set = %s\n",key_to_set);
    value_to_set = getValue(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");
	printf("value_to_set = %s\n",value_to_set);	
	existing_value = get_env(core, key_to_set);
	printf("existing_value = %s\n", existing_value);
	
	if (existing_value)
	    // remove node
	else
	    //add new node to list
	

}