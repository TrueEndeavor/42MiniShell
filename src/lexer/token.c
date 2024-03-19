/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:56 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/19 15:30:22 by lannur-s         ###   ########.fr       */
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

char	*token_type_to_str(int type)
{
	if (type == T_WORD)
		return ("T_WORD");
	if (type == T_DOLLAR)
		return ("$");
	if (type == T_VARIABLE)
		return ("T_VARIABLE");
	if (type == T_IO_NUMBER)
		return ("T_IO_NUMBER");
	if (type == T_PIPE)
		return ("T_PIPE");
	if (type == T_REDIRECT_IN)
		return ("T_REDIRECT_IN");
	if (type == T_REDIRECT_OUT)
		return ("T_REDIRECT_OUT");
	if (type == T_APPEND_OUT)
		return ("T_APPEND_OUT");
	if (type == T_HEREDOC)
		return ("T_HEREDOC");
	if (type == T_LINEBREAK)
		return ("T_LINEBREAK");
	if (type == T_QUOTED_STRING)
		return ("T_QUOTED_STRING");
	if (type == T_DOUBLE_QUOTED_STRING)
		return ("DOUBLE_QUOTED_STRING");
	return ("Not stringable");
}

char	*token_type_to_symbol(int type)
{
	if (type == T_WORD)
		return ("T_WORD");
	if (type == T_DOLLAR)
		return ("$");
	if (type == T_VARIABLE)
		return ("T_VARIABLE");
	if (type == T_IO_NUMBER)
		return ("T_IO_NUMBER");
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
	if (type == T_QUOTED_STRING)
		return ("T_QUOTED_STRING");
	if (type == T_DOUBLE_QUOTED_STRING)
		return ("DOUBLE_QUOTED_STRING");
	return ("Not stringable");
}

/* char	*token_to_str(t_token_T *token)
{
	char	*type_str;
	char	*template;
	char	*str;

	type_str = NULL;
	template = NULL;
	str = NULL;
	type_str = token_type_to_str(token->type);
	template = "<type='%s', int_type='%d', value='%s'>";
	str = ft_calloc(strlen(type_str) + strlen(template) + 8, \
		sizeof(char));
	sprintf(str, template, type_str, token->type, token->value);
	return (str);
} */
