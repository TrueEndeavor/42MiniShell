/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:18 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/12 10:23:19 by lannur-s         ###   ########.fr       */
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

int is_valid_variable_char(char c) 
{
    return (ft_isalnum(c) || c == '_');
}

t_token_T	*lexer_parse_variable(t_lexer_T *lexer)
{
	char		*value;
	char		*new_value;
	int			new_size;
	t_token_T	*ret_token;

	ret_token = NULL;
	if ((lexer->c) == '?')
	{
		lexer_advance(lexer);
		return (init_token("?", T_EXITCODE));
	}
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (is_valid_variable_char(lexer->c))
	{
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		if (!new_value)
		{
			free (value);
			return (NULL);
		}
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
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
	char		*new_value;
	int			new_size;
	t_token_T	*ret_token;

	ret_token = NULL;
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (ft_isprint(lexer->c) && (!ft_iswhitespace(lexer->c)))
	/* while (ft_isalpha(lexer->c) || ft_isdigit(lexer->c) ||
		(lexer->c == '_') || (lexer->c == '-') || \
		(lexer->c == '/') || (lexer->c == '.'))	 */
	{
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		if (!new_value)
		{
			free (value);
			return (NULL);
		}
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		lexer_advance(lexer);
	}
    ret_token = init_token(value, T_WORD);
	return (ret_token);
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
	return (init_token(value, T_IO_NUMBER));
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
		if (lexer->c == '>' && lexer_peek(lexer, 1) == '>')
		{
			lexer_advance(lexer);
			return (lexer_advance_with(lexer, init_token(">>", T_APPEND_OUT)));
		}
		if (lexer->c == '<' && lexer_peek(lexer, 1) == '<')
			return (handle_heredoc_token(lexer));			
		if (lexer->c == '>' || lexer->c == '<')
			return (handle_redirect_tokens(lexer));
		if (lexer->c == '$')
			return (handle_variable_token(lexer));		
		if ((lexer->c == 34) || (lexer->c == 39))
			return (handle_quoted_strings(lexer));			
		if (lexer->c == '\0')
			break ;
 		/*if (ft_isalpha(lexer->c) || ft_isdigit(lexer->c) ||
		(lexer->c == '_') || (lexer->c == '-') || \
		(lexer->c == '/') || (lexer->c == '.')) */
		if (ft_isprint(lexer->c) && (!ft_iswhitespace(lexer->c)))
			return (handle_expected_tokens(lexer));
		handle_unexpected_character(lexer);
		break ;
	}
	return (init_token(";", T_LINEBREAK));
}
	
	
	
	
	/**** OLD PARSE WORD FUNCTION WITH NAME VALIDATIONS AND FLAGS FOR VARIABLE
	
	t_token_T	*lexer_parse_word(t_lexer_T *lexer, int is_variable, \
							int is_possible_name)
{
	char		*value;
	char		*new_value;
	int			new_size;
	int			is_name_by_default;
	t_token_T	*ret_token;

	ret_token = NULL;
	is_name_by_default = 1;
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	//while (ft_isascii(lexer->c))
	while (ft_isalpha(lexer->c) || ft_isdigit(lexer->c) ||
		(lexer->c == '_') || (lexer->c == '-') || \
		(lexer->c == '/') || (lexer->c == '.'))	
	{
		if (!is_valid_variable_char(lexer->c))
				is_possible_name = 0;
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		if (!new_value)
		{
			free (value);
			return (NULL);
		}
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		lexer_advance(lexer);
	}
	if (is_variable & is_possible_name & is_name_by_default)
	{
        ret_token = init_token("$", T_VARIABLE);	
	}
	else if (is_possible_name & is_name_by_default)
	{
        ret_token = init_token(value, T_NAME);
    } 
    else if (!(is_possible_name & is_name_by_default))
    {
        ret_token = init_token(value, T_WORD);
    }
	return (ret_token);
}

	*/