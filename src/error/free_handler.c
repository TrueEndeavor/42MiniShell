/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:27:03 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/12 10:01:37 by trysinsk         ###   ########.fr       */
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
        free((current)->value);
        printf ("freed value\n");
        next = current->next;
        free(current);
        current = next;
    }
}