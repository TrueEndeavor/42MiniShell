/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:03 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/13 11:50:20 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free_tok_list(t_token_T **token_head)
{
    t_token_T   *helper;
    
    helper = NULL;
    if (token_head)
    {
        printf ("commencing free of token list\n");
        while ((*token_head) != NULL)
        {
            helper = (*token_head)->next;
            free((*token_head)->value);
            free(*token_head);
            (*token_head) = helper;
        }
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
            free(env->name);
            free(env->value);
            free(env);
            env = next;
        }
    }
}
