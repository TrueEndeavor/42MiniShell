/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:20:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/21 11:19:59 by trysinsk         ###   ########.fr       */
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

t_token_T	*handle_expected_tokens(t_lexer_T *lexer)
{	
	if (lexer->c == '$')
	{
		if (is_valid_variable_char(lexer_peek(lexer, 1)))
			return (handle_variable_token(lexer));
		return (NULL);
	}
	if (ft_isprint(lexer->c) && (!ft_iswhitespace(lexer->c)))
		return (handle_word_token(lexer));
	if (ft_isdigit(lexer->c))
		return (lexer_advance_with(lexer, lexer_parse_number(lexer)));
	return (NULL);
}


t_token_T	*handle_dollar_token(t_lexer_T *lexer)
{
	if (lexer->c == '$')
	{
		if (ft_iswhitespace(lexer_peek(lexer, 1))
			|| lexer_peek(lexer, 1) == '\0')
		{
			lexer_advance(lexer);
			return (init_token(ft_strdup("$"), T_DOLLAR));
		}
		else
			return (handle_variable_token(lexer));
	}
	return (NULL);
}
