/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:30 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/22 12:33:35 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*handle_expected_tokens(t_lexer_T *lexer)
{
	if (ft_isalpha(lexer->c) || (lexer->c == '_'))
		return (handle_word_token(lexer, IS_NOT_A_VARIABLE, \
									IS_A_POSSIBLE_NAME));
	if (lexer->c == '$')
		return (handle_word_token(lexer, IS_A_VARIABLE, \
									IS_A_POSSIBLE_NAME));		
	if (ft_isalpha(lexer->c) || ft_isdigit(lexer->c) || \
		(lexer->c == '_') || (lexer->c == '-') || \
		(lexer->c == '/') || (lexer->c == '.'))
		return (lexer_advance_with(lexer, init_token("$", T_DOLLAR)));
	if (ft_isdigit(lexer->c))
		return (handle_number_token(lexer));
	if (lexer->c == '|')
		return (handle_pipe_token(lexer));
	return (NULL);

}

t_token_T	*handle_redirect_tokens(t_lexer_T *lexer)
{
	if (lexer->c == '>')
	{
		if (lexer_peek(lexer, 1) == '>')
			return (handle_append_out_token(lexer));
		return (handle_redirect_out_token(lexer));
	}
	if (lexer->c == '<')
	{
		if (lexer_peek(lexer, 1) == '<')
			return (handle_heredoc_token(lexer));
		return (handle_redirect_in_token(lexer));
	}
	return (NULL);
}
