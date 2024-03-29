/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 13:08:29 by trysinsk         ###   ########.fr       */
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

t_token_T	*lexer_parse_variable(t_lexer_T *lexer)
{
	char		*value;
	char		*copy;
	int			new_size;
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
		new_size = ft_strlen(value) + 2;
		copy = ft_calloc(new_size, sizeof(char));
		if (!copy)
		{
			free (value);
			return (NULL);
		}
		ft_strlcpy(copy, value, new_size);
		free(value);
		value = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(value, copy, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		free(copy);
		lexer_advance(lexer);
	}
	ret_token = init_token(value, T_VARIABLE);
	return (ret_token);
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
t_token_T	*lexer_parse_word(t_lexer_T *lexer)
{
	char		*value;
	char		*copy;
	int			new_size;
	t_token_T	*ret_token;
	bool		quote_flag;

	quote_flag = false;
	ret_token = NULL;
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (ft_isprint(lexer->c)
		&& ((quote_flag && (lexer_peek(lexer, 1) != '\''
					|| lexer_peek(lexer, 1) != '\"'))
			|| (!quote_flag && !ft_iswhitespace(lexer->c))))
	{
		printf("quote flag= %d; lexer->c=%c\n", quote_flag, lexer->c);
		if (lexer->c == '\'' || lexer->c == '\"')
			quote_flag = !quote_flag;
		new_size = ft_strlen(value) + 2;
		copy = ft_calloc(new_size, sizeof(char));
		if (!copy)
		{
			free (value);
			return (NULL);
		}
		ft_strlcpy(copy, value, new_size);
		free(value);
		value = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(value, copy, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		free(copy);
		lexer_advance(lexer);
	}
	printf("value =%s=\n", value);
	if (!is_nested_quotes(value))
		return (NULL);
	ret_token = init_token(value, T_WORD);
	return (ret_token);
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
		if (lexer->c == '$')
		{
			return (handle_dollar_token(lexer));
		}
		if (lexer->c == '\0')
			break ;
		if (ft_isprint(lexer->c) && (!ft_iswhitespace(lexer->c)))
			return (handle_expected_tokens(lexer));
		handle_unexpected_character(lexer);
		break ;
	}
	return (init_token(ft_strdup("\0"), T_LINEBREAK));
}
