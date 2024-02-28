/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/28 11:55:47 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env(t_core_struct *core, char *key_value_pair)
{
	t_env_list	*head;
	t_env_list	*new;
	char    *key_to_set;
	char    *value_to_set;
	int modified_flag;
	
	new = NULL;
	modified_flag = 0;
	head = core->env_list;
    key_to_set = getKey(key_value_pair);
    value_to_set = getValue(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");
	while (core->env_list)
	{
		printf("...searching= %s\n",core->env_list->name);
		if ((ft_strlen((core->env_list)->name) == ft_strlen(key_to_set)) && 
			(ft_strcmp((core->env_list)->name, key_to_set) == 0))
		{
			if (value_to_set)
			{
	            free((core->env_list)->value);
	            (core->env_list)->value = ft_strdup(value_to_set);
	            if (!(core->env_list)->value)
	                return ;
			}
		}
		 core->env_list = (core->env_list)->next;
	}

}

/* void	append _env(t_core_struct *core, char *key_value_pair)
{
	t_env_list	*head;
	t_env_list	*new;
	char    *key_to_set;
	char    *value_to_set;
	int modified_flag;
	
	new = NULL;
	modified_flag = 0;
	head = core->env_list;
    key_to_set = getKey(key_value_pair);
    value_to_set = getValue(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");
	while (core->env_list)
	{
		printf("...searching= %s\n",core->env_list->name);
		if ((ft_strlen((core->env_list)->name) == ft_strlen(key_to_set)) && 
			(ft_strcmp((core->env_list)->name, key_to_set) == 0))
		{
			if (value_to_set)
			{
	            free((core->env_list)->value);
	            (core->env_list)->value = ft_strdup(value_to_set);
	            if (!(core->env_list)->value)
	                return ;
			}
		}
		 core->env_list = (core->env_list)->next;
	}

}
 */

void	set_env(t_core_struct *core, char *key_value_pair)
{
	t_env_list	*head;
	t_env_list	*new;
	//int	len;
	char    *key_to_set;
	char    *value_to_set;
	int modified_flag;
	//char    *existing_value;
	head = core->env_list;
	//printf("address of el in ----set %p\n", core->env_list);	
	modified_flag = 0;
	new = NULL;
	//printf("key_value_pair = %s\n",key_value_pair);
    key_to_set = getKey(key_value_pair);
	//printf("key_to_set = %s\n",key_to_set);
    value_to_set = getValue(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");

	while (core->env_list)
	{
		if ((ft_strlen((core->env_list)->name) == ft_strlen(key_to_set)) && 
			(ft_strcmp((core->env_list)->name, key_to_set) == 0))
		{
			if (value_to_set != NULL)
			{
            printf("hello%s...\n", (core->env_list)->value);   
                if (((core->env_list)->value != NULL))
                {
	                free((core->env_list)->value);
	                (core->env_list)->value = NULL;
				}
	            (core->env_list)->value = ft_strdup(value_to_set);
			printf("value_to_set = %s\n",(core->env_list)->value);
			}
            if (!(core->env_list)->value)
                panic ("env list value empty");
		    modified_flag = 1;
			//break ;
		}
	    core->env_list = (core->env_list)->next;
    }
	if (!value_to_set && modified_flag == 0)
    {
		printf("⚠️no value to set for key= %s\n",key_to_set);
		core->env_list = head;
	    new = ft_lstnew_env(key_to_set, NULL);
		if (!new)
			ft_lstclear_env(&core->env_list, free);
        ft_lstadd_back_env(&core->env_list, new);			
    }
    else if (modified_flag == 0)
    { 
		core->env_list = head;
		printf("adding new\n");
		printf("list size %d\n", ft_lstsize_env(core->env_list));	
		printf("key_before_replace = %s\n",(core->env_list)->name);		
		printf("value_before_replace = %s\n",(core->env_list)->value);		
    	new = ft_lstnew_env(key_to_set, value_to_set);
		if (!new)
			ft_lstclear_env(&core->env_list, free);
        ft_lstadd_back_env(&core->env_list, new);	
	}
	printf("address of env_list in ----end of set %p\n", core->env_list);		
	printf("address of head in ----end of set %p\n", head);		
	core->env_list = head;
     //add new node to list
}