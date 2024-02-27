/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 17:08:26 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **convert_env_to_stringarray(t_env_list *env_list)
{
    t_env_list *env_orig;
    char	*temp_envp;
    char	**new_envp;
    int     i;
	int		count;

	count = 0;
	temp_envp = NULL;
	env_orig = env_list;
	if (env_list)
	{
		count++;
		while (env_list->next)
		{
			count++;
			env_list = env_list->next;
		}
	}
    new_envp = malloc(sizeof(char *) * count + 1);
    if (!new_envp)  
            return (NULL);
    i = 0;
    while (env_orig)
    {
        temp_envp = ft_strjoin(env_orig->name,"=");
        new_envp[i] = ft_strjoin(temp_envp, env_orig->value);
        free(temp_envp);
		if (!new_envp[i])
		{
		    free(new_envp);
		    return (NULL);
        }
        
		i++;
	    env_orig = env_orig->next;
	}
	new_envp[i] = NULL;
    return (new_envp); 
} 

char *getKey(char *s)
{	char *result;
	
	result = ft_strchr(s, '=');
	if (result)
        return(ft_substr(s, 0, (ft_strlen(s) - ft_strlen(result))));
    else    
        return(s);
}

char *getValue(char *s)
{
 	char *result;
	
	result = ft_strchr(s, '=');
	if (result)
        return (ft_substr(s, (ft_strlen(s) - ft_strlen(result)) + 1, ft_strlen(s)));
    else
        return (NULL);
}

t_env_list    *init_env(char **envp)
{
	t_env_list	*minishell_envp_head;
    t_env_list	*new;
    int     i;

	if (!envp || !*envp)
		return (NULL);
	minishell_envp_head = NULL;
    i = 0;
    while (envp[i])
	{
		if ((ft_strchr(envp[i], '=')) != NULL)
		{
			if (!getKey(envp[i]) || !getValue(envp[i]))
				return ((ft_lstclear_env(&minishell_envp_head, free), NULL));
			new = ft_lstnew_env(getKey(envp[i]), getValue(envp[i]));
			if (!new)
				return ((ft_lstclear_env(&minishell_envp_head, free), NULL));
			ft_lstadd_back_env(&minishell_envp_head, new);
		}
		i++;
	}
	printf("minishell_envp_head address=%p\n", minishell_envp_head);	
    return (minishell_envp_head);
}

int     count_of_env(char **envp)
{
    int		count;
    
    count =0;
	while (*envp != NULL)
	{
	    if (*envp[0] != '\0')
		    count++;
		envp++;
    }
    return (count);
}

int     count_of_env_list(t_env_list **env_list)
{
    int		count;
    
    count =0;
	if (*env_list)
	{
printf("address count_of_env_list%p\n", env_list);
display_env_from_list(env_list);
		count++;
		while ((*env_list)->next)
		{
			count++;
			*env_list = (*env_list)->next;
		}
	}
	return (count);
}

void	display_env(int count, char	**envp)
{
    int i;
    
    i = 1;
    while (i < count)
	{
	    if ((ft_strchr(envp[i], '=')) != NULL)
    		printf("%s\n",envp[i]);
	    i++;
	}
}

void	display_env_from_list(t_env_list **env_list)
{
    int i;
    
    i = 1;
        
    printf("list size in display_env_from_list%d\n",ft_lstsize_env(*env_list));
    
	if (*env_list)
		while ((*env_list)->next)
		{
			if ((*env_list)->value != NULL)
				printf("%s%s%s\n", (*env_list)->name, "=", (*env_list)->value);
			*env_list = (*env_list)->next;
		}
}