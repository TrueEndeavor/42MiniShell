/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 17:01:50 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_env_list **env_list, char *key_value_pair)
{
	t_env_list	**head;
	t_env_list	*new;
	//int	len;
	char    *key_to_set;
	char    *value_to_set;
	int modified_flag;
	//char    *existing_value;
	head = env_list;
	printf("address of el in ----set %p\n", env_list);	
	modified_flag = 0;
	new = NULL;
	printf("key_value_pair = %s\n",key_value_pair);
    key_to_set = getKey(key_value_pair);
	printf("key_to_set = %s\n",key_to_set);
    value_to_set = getValue(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");
	printf("value_to_set = %s\n",value_to_set);	
	while (*env_list)
	{
	printf("...searching= %s\n",(*env_list)->name);	
		if ((ft_strlen((*env_list)->name) == ft_strlen(key_to_set)) && 
			!(ft_strcmp((*env_list)->name, key_to_set)))
		{
            //free((*env_list)->value);
            (*env_list)->value = ft_strdup(value_to_set);
            if (!(*env_list)->value)
                panic ("env list value empty");
		    modified_flag = 1;
		}
	    *env_list = (*env_list)->next;
    }
    printf("hello\n");   
    if (!value_to_set && modified_flag == 0)
    {
    
	    new = ft_lstnew_env(key_to_set, "");
		//if (!new)
		//	ft_lstclear_env(env_list, free);
        ft_lstadd_back_env(env_list, new);			
    }
    else if (modified_flag == 0)
    {
    	new = ft_lstnew_env(key_to_set, value_to_set);
		//if (!new)
		//	ft_lstclear_env(env_list, free);
        ft_lstadd_back_env(env_list, new);			
	}
	printf("address of env_list in ----end of set %p\n", env_list);		
	printf("address of head in ----end of set %p\n", head);		
	env_list = head;
     //add new node to list
}