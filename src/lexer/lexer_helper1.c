/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:20:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/02 19:52:40 by lannur-s         ###   ########.fr       */
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

t_token_T	*handle_alphabet_token(t_lexer_T *lexer)
{
	return (lexer_advance_with(lexer, lexer_parse_id(lexer)));
}

t_token_T	*handle_number_token(t_lexer_T *lexer)
{
	return (lexer_advance_with(lexer, lexer_parse_number(lexer)));
}

t_token_T	*handle_pipe_token(t_lexer_T *lexer)
{
	return (lexer_advance_current(lexer, PIPE));
}

t_token_T	*handle_append_out_token(t_lexer_T *lexer)
{
	return (lexer_advance_with(lexer, init_token(">>", APPEND_OUT)));
}

t_token_T	*handle_redirect_out_token(t_lexer_T *lexer)
{
	return (lexer_advance_current(lexer, REDIRECT_OUT));
}
