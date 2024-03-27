/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:17:29 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/27 17:29:43 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    key_to_set = getKey(key_value_pair);
    value_to_set = getValue(key_value_pair);
	if (!key_to_set)
		panic ("key to set not found");
	printf("............key_to_set = %s\n",key_to_set);
	if (!is_valid_variable_name(key_to_set) || (ft_strchr(key_to_set, '=') != NULL))
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", key_to_set);
		core->exit_code = EXIT_FAILURE;
	}
	else
	{		
		while (core->env_list)
		{
			if ((ft_strlen((core->env_list)->name) == ft_strlen(key_to_set)) && 
				(ft_strcmp((core->env_list)->name, key_to_set) == 0))
			{
				if (*value_to_set != '\0')
				{
					if (((core->env_list)->value != NULL))
						free((core->env_list)->value);
		            (core->env_list)->value = ft_strdup(value_to_set);
				}
				else
				{
				printf("dsssssssssss............\n");
	                if (((core->env_list)->value != NULL))
		                free((core->env_list)->value);
	                (core->env_list)->value = "";
				}
/* 	            if (!(core->env_list)->value)
	                panic ("env list value empty"); */
			    modified_flag = 1;
			}
		    core->env_list = (core->env_list)->next;
	    }
	    printf("............value_to_set = %s & modified_flag = %d \n",value_to_set, modified_flag);
		if (!value_to_set && modified_flag == 0)
	    {
			core->env_list = head;
		    new = ft_lstnew_env(key_to_set, NULL);
		    printf("adding the new variable with empty value\n");
			if (!new)
				ft_lstclear_env(&core->env_list, free);
	        ft_lstadd_back_env(&core->env_list, new);			
	    }
	    else if (modified_flag == 0)
	    { 
			core->env_list = head;
	    	new = ft_lstnew_env(key_to_set, value_to_set);
			if (!new)
				ft_lstclear_env(&core->env_list, free);
	        ft_lstadd_back_env(&core->env_list, new);	
		}
	}
	core->env_list = head;
}