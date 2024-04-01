/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:13:03 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 08:13:03 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*lexer_parse_variable(t_lexer_T *lexer)
{
	char		*value;
	t_token_T	*ret_token;

	ret_token = NULL;
	if ((lexer->c) == '?')
	{
		lexer_advance(lexer);
		return (init_token(ft_strdup("$?"), T_EXITCODE));
	}
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (is_valid_variable_char(lexer->c))
	{
		extend_string(&value, lexer->c);
		lexer_advance(lexer);
	}
	ret_token = init_token(value, T_VARIABLE);
	return (ret_token);
}
