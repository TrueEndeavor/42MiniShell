/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:56 by lannur-s          #+#    #+#             */
/*   Updated: 2024/01/25 15:30:40 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*init_token(char *value, int type)
{
	t_token_T		*token;

	token = ft_calloc(1, sizeof(t_token_T));
	token->value = value;
	token->type = type;
	return (token);
}

char	*token_type_to_str(int type)
{
	if (type == TOKEN_ID)
		return ("TOKEN_ID");
	if (type == TOKEN_INT)
		return ("TOKEN_INT");
	if (type == TOKEN_PIPE)
		return ("TOKEN_PIPE");
	if (type == TOKEN_REDIRECT_IN)
		return ("TOKEN_REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("TOKEN_REDIRECT_OUT");
	if (type == TOKEN_APPEND_OUT)
		return ("TOKEN_APPEND_OUT");
	if (type == TOKEN_HEREDOC)
		return ("TOKEN_HEREDOC");
	if (type == TOKEN_EOF)
		return ("TOKEN_EOF");
	return ("Not stringable");
}

char	*token_to_str(t_token_T *token)
{
	char	*type_str;
	char	*template;
	char	*str;

	type_str = NULL;
	template = NULL;
	str = NULL;
	type_str = token_type_to_str(token->type);
	template = "<type=%s, int_type=%d, value=%s>";
	str = ft_calloc(strlen(type_str) + strlen(template) + 8, \
		sizeof(char));
	sprintf(str, template, type_str, token->type, token->value);
	return (str);
}
