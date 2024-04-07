/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:16:10 by trysinsk          #+#    #+#             */
/*   Updated: 2024/04/07 18:27:10 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(t_core_struct *core, char **str)
{
	char	*ret;

	ret = ft_strdup(get_env(core, (*str)));
	free(*str);
	return (ret);
}

char	*ft_here(char **value)
{
	char	*ret;

	ret = ft_strjoin("$", (*value));
	free(*value);
	return (ret);
}

t_token_T	*search_for(t_token_T *current, int target_token_type)
{
	t_token_T	*tok;

	tok = current;
	if (tok)
	{
		if (tok->type == target_token_type)
		{
			return (tok);
		}
	}
	return (NULL);
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
