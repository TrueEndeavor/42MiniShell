/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:03 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/12 12:39:11 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free_tok_list(t_token_T **token_head)
{
    t_token_T   *current;
    t_token_T   *next;
    
    current = (*token_head);
    while (current!= NULL)
    {
        printf ("value : %s ", (current)->value);
        free((current)->value);
        printf ("freed\n");
        next = current->next;
        free(current);
        current = next;
    }
}

void    ft_free_env(t_env_list *env)
{
    t_env_list  *next;
    
    if (env)
    {
        while (env != NULL)
        {
            next = env->next;
            printf ("freeing: %s\n", env->name);
            free(env->name);
            printf ("and: %s\n", env->value);
            free(env->value);
            printf ("freeing node\n");
            free(env);
            env = next;
        }
    }
}