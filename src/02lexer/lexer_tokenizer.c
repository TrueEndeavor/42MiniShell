/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 11:44:20 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Advances the lexer, creating a token with the current character, 
 * and moves forward
 *
 * This function creates a token for the character at the current position in 
 * the shell command and then advance the lexer to the subsequent character. It 
 * is particularly useful for handling single-character tokens or tokens 
 * associated with individual characters
 *
 * @param lexer The lexer to advance
 * @param type The type of the token to create
 *
 * @return A token representing the current character
 */
t_token_T	*lexer_advance_current(t_lexer_T *lexer, int type)
{
	char		*value;
	t_token_T	*token;

	value = ft_calloc(2, sizeof(char));
	value[0] = lexer->c;
	value[1] = '\0';
	token = init_token(value, type);
	lexer_advance(lexer);
	return (token);
}

/**
 * Scans to find the next token from the shell command using the lexer
 *
 * This is the main entry point for obtaining tokens from the shell command
 * It delegates to specific token-parsing functions based on the type of 
 * characters encountered in the shell command
 *
 * @param lexer The lexer to extract tokens with
 *
 * @return The next token in the shell command
 */
t_token_T	*lexer_scan_token(t_lexer_T *lexer)
{
	while (lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);
		if (lexer->c == '|')
			return (lexer_advance_current(lexer, T_PIPE));
		if (lexer->c == '>' || lexer->c == '<')
			return (handle_redirect_tokens(lexer));
		if (lexer->c == '\0')
			break ;
		if (ft_isprint(lexer->c) && (!ft_iswhitespace(lexer->c)))
			return (handle_expected_tokens(lexer));
		else
			handle_unexpected_character(lexer);
		break ;
	}
	return (init_token(ft_strdup("\0"), T_LINEBREAK));
}
