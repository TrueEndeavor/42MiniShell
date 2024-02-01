/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/01/25 15:16:15 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Advances the lexer to the next character and associates the current
 * character with the provided token
 *
 * This function is a utility for lexer advancement. It moves the lexer to the
 * subsequent position in the shell command and associates the latest character
 * encountered with the provided token. The token, which may already contain
 * characters, is seamlessly extended or constructed during the tokenization 
 * process
 *
 * @param lexer The lexer to advance
 * @param token The token being constructed/extended with the current character
 *
 * @return The same token provided, now representing an extended or newly 
 *         constructed version with the current character
 */
t_token_T	*lexer_advance_with(t_lexer_T *lexer, t_token_T *token)
{
	lexer_advance(lexer);
	return (token);
}

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
 * Parses alphabets (word) from the shell command and creates a corresponding 
 * token
 *
 * This function is responsible for recognizing and creating a token for 
 * alphabets (word)
 * It iterates through the characters that form the identifier until
 * a non-alphabetic character is encountered
 *
 * @param lexer The lexer to parse with
 *
 * @return A token representing the parsed identifier
 */
t_token_T	*lexer_parse_id(t_lexer_T *lexer)
{
	char	*value;
	char	*new_value;
	int		new_size;

	value = ft_calloc(1, sizeof(char));
	while (ft_isalpha(lexer->c))
	{
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_ID));
}

/**
 * Parses a number from the shell command and creates a corresponding token
 *
 * This function is responsible for recognizing and creating a token for a 
 * numeric value. It iterates through the characters that form the number until 
 * a non-digit character is encountered
 *
 * @param lexer The lexer to parse with
 *
 * @return A token representing the parsed number
 */
t_token_T	*lexer_parse_number(t_lexer_T *lexer)
{
	char	*value;
	char	*new_value;
	int		new_size;

	value = ft_calloc(1, sizeof(char));
	while (ft_isdigit(lexer->c))
	{
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		lexer_advance(lexer);
	}
	return (init_token(value, TOKEN_ID));
}

/**
 * Retrieves the next token from the shell command using the lexer
 *
 * This is the main entry point for obtaining tokens from the shell command
 * It delegates to specific token-parsing functions based on the type of 
 * characters encountered in the shell command
 *
 * @param lexer The lexer to extract tokens with
 *
 * @return The next token in the shell command
 */
t_token_T	*lexer_next_token(t_lexer_T *lexer)
{
	while (lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);
		if (ft_isalpha(lexer->c) || ft_isdigit(lexer->c) || lexer->c == '|')
			return (handle_expected_tokens(lexer));
		if (lexer->c == '>' && lexer_peek(lexer, 1) == '>')
			return (handle_append_out_token(lexer));
		if (lexer->c == '>' || lexer->c == '<')
			return (handle_redirect_tokens(lexer));
		if (lexer->c == '\0')
			break ;
		handle_unexpected_character(lexer);
		break ;
	}
	return (init_token(0, TOKEN_EOF));
}