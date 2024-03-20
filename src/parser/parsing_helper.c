/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:16:10 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/20 11:09:28 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_expand(t_core_struct *core, char **file_name)
{
    char *ret;

    ret = ft_strdup(get_env(core, (*file_name)));
    free(*file_name);
    return (ret);
}

char    *ft_here(char **value)
{
    char *ret;

    ret = ft_strjoin("$", (*value));
    free(*value);
    return (ret);
}

t_token_T   *search_for(t_token_T *current, int target_token_type)
{
	t_token_T *tok = current;
	if (tok->type == target_token_type)
	{
		return tok;
	}
	return NULL;
}

t_token_T	*peek_next_token(t_token_T *current_token)
{
	if (current_token && current_token->next)
	{
		return (current_token->next);
	}
	return (NULL);
}


t_token_T	*advance_token(t_token_T **current_token)
{
	if (*current_token && (*current_token)->next)
	{
		return ((*current_token)->next);
	}
	return (NULL);
}