/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:38:25 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 09:07:21 by lannur-s         ###   ########.fr       */
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
{
    return(ft_substr(s, 0, (ft_strlen(s) - ft_strlen(ft_strchr(s, '=')))));
}

char *getValue(char *s)
{
    return(ft_substr(s, (ft_strlen(s) - ft_strlen(ft_strchr(s, '='))) + 1, ft_strlen(s)));
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

int     count_of_env_list(t_env_list *env_list)
{
    int		count;
    
    count =0;
	if (env_list)
	{
		count++;
		while (env_list->next)
		{
			count++;
			env_list = env_list->next;
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

void	display_env_from_list(t_env_list *env_list)
{
    int i;
    
    i = 1;
    
	if (env_list)
		while (env_list->next)
		{
			printf("%s%s%s\n", env_list->name, "=", env_list->value);
			env_list = env_list->next;
		}
}