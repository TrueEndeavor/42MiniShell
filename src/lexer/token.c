/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:01:56 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/05 21:59:31 by marvin           ###   ########.fr       */
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
	if (type == WORD)
		return ("WORD");
	if (type == NAME)
		return ("NAME");
	if (type == ASSIGNMENT_WORD)
		return ("ASSIGNMENT_WORD");
	if (type == IO_NUMBER)
		return ("IO_NUMBER");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == APPEND_OUT)
		return ("APPEND_OUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == LINEBREAK)
		return ("LINEBREAK");
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
	template = "<type='%s', int_type='%d', value='%s'>";
	str = ft_calloc(strlen(type_str) + strlen(template) + 8, \
		sizeof(char));
	sprintf(str, template, type_str, token->type, token->value);
	return (str);
}
