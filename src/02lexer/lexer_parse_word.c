/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:12:02 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 08:12:02 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*initialize_string(char **value)
{
	*value = ft_calloc(1, sizeof(char));
	if (!*value)
		return (NULL);
	(*value)[0] = '\0';
	return (*value);
}

char	*read_string(t_lexer_T **lexer)
{
	char		*value;
	bool		quote_flag;

	quote_flag = false;
	initialize_string(&value);
	while (ft_isprint((*lexer)->c) \
		&& ((quote_flag && (lexer_peek((*lexer), 1) != '\'' \
		|| lexer_peek((*lexer), 1) != '\"')) \
		|| (!quote_flag && !is_metacharacter((*lexer)->c))))
	{
		printf("quote flag= %d; lexer->c=%c\n", quote_flag, (*lexer)->c);
		if ((*lexer)->c == '\'' || (*lexer)->c == '\"')
			quote_flag = !quote_flag;
		extend_string(&value, (*lexer)->c);
		lexer_advance(*lexer);
	}
	return (value);
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
	t_token_T	*ret_token;
	char		*value;

	ret_token = NULL;
	if ((lexer->c) == '$' && (lexer_peek(lexer, 1) == '?'))
	{
		lexer_advance(lexer);
		return (init_token(ft_strdup("$?"), T_EXITCODE));
	}
	value = read_string(&lexer);
	printf("value =%s=\n", value);
	if (!is_nested_quotes(value))
		return (NULL);
	ret_token = init_token(value, T_WORD);
	return (ret_token);
}
