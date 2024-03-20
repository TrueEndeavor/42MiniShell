/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:20:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/20 14:12:45 by trysinsk         ###   ########.fr       */
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
t_token_T	*handle_word_token(t_lexer_T *lexer)
{
	return (lexer_parse_word(lexer));
}

t_token_T	*handle_variable_token(t_lexer_T *lexer)
{
	lexer_advance(lexer);
	return (lexer_parse_variable(lexer));
}

/* t_token_T	*handle_number_token(t_lexer_T *lexer)
{
	return (lexer_advance_with(lexer, lexer_parse_number(lexer)));
} */

/* t_token_T	*handle_pipe_token(t_lexer_T *lexer)
{
	return (lexer_advance_current(lexer, T_PIPE));
} */

t_token_T	*handle_append_out_token(t_lexer_T *lexer)
{
	lexer_advance(lexer);
	return (lexer_advance_with(lexer, init_token(">>", T_APPEND_OUT)));
}

/* t_token_T	*handle_redirect_out_token(t_lexer_T *lexer)
{
	return (lexer_advance_current(lexer, T_REDIRECT_OUT));
} */
