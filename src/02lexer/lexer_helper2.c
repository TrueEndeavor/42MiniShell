/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:38:43 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 10:11:13 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** *
 * All the helper function that handle the specific characters as they 
 * are encountered
 *
 * @param lexer The lexer to advance
 *
 * @return A token representing the identifier
 * ************************************************************************* */

t_token_T	*handle_heredoc_token(t_lexer_T *lexer)
{
	lexer_advance(lexer);
	return (lexer_advance_with(lexer, init_token(ft_strdup("<<"), T_HEREDOC)));
}

t_token_T	*handle_redirect_in_token(t_lexer_T *lexer)
{
	return (lexer_advance_current(lexer, T_REDIRECT_IN));
}

t_token_T	*handle_append_out_token(t_lexer_T *lex)
{
	lexer_advance(lex);
	return (lexer_advance_with(lex, init_token(ft_strdup(">>"), T_APPEND_OUT)));
}

t_token_T	*handle_redirect_tokens(t_lexer_T *lexer)
{
	if (lexer->c == '>')
	{
		if (lexer_peek(lexer, 1) == '>')
			return (handle_append_out_token(lexer));
		return (lexer_advance_current(lexer, T_REDIRECT_OUT));
	}
	if (lexer->c == '<')
	{
		if (lexer_peek(lexer, 1) == '<')
			return (handle_heredoc_token(lexer));
		return (handle_redirect_in_token(lexer));
	}
	return (NULL);
}
