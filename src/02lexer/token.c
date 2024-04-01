/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:56 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/31 20:54:00 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*init_token(char *value, int type)
{
	t_token_T		*token;

	token = ft_calloc(1, sizeof(t_token_T));
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

char	*token_type_to_symbol(int type)
{
	if (type == T_DOLLAR)
		return ("$");
	if (type == T_PIPE)
		return ("|");
	if (type == T_REDIRECT_IN)
		return ("<");
	if (type == T_REDIRECT_OUT)
		return (">");
	if (type == T_APPEND_OUT)
		return (">>");
	if (type == T_HEREDOC)
		return ("<<");
	if (type == T_LINEBREAK)
		return ("newline");
	return ("Not stringable");
}
