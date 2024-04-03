/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:04:53 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/03 16:41:59 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets up lexer(language interpreter) for the given shell command at the prompt
 * Allocates memory in heap, and places it at the first character in the shell
 * command given at the prompt
 *
 * @param src The command to be processed by the lexer
 *
 * @return A pointer to the initialized lexer, pointing to the first char
 */
t_lexer_T	*init_lexer(char *src)
{
	t_lexer_T	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer_T));
	if (!lexer)
		return (NULL);
	lexer->src = src;
	lexer->src_size = ft_strlen(src);
	lexer->i = 0;
	lexer->c = src[lexer->i];
	return (lexer);
}

/**
 * Peeks at the character in the shell command at the specified offset
 *
 * @param lexer The lexer to peek with
 * @param offset The offset to look ahead
 *
 * @return The character at the peeked position
 */
char	lexer_peek(t_lexer_T *lexer, int offset)
{
	return (lexer->src[min_int(lexer->i + offset, lexer->src_size)]);
}

/**
 * Skips over whitespace characters in the source code
 * ' ' (space), '\f' (formfeed), '\t' (tab), '\n' (newline), 
 * '\r' (carriage return), and '\v'(vertical tab)
 *
 * @param lexer The lexer to skip whitespace in
 */
void	lexer_skip_whitespace(t_lexer_T *lexer)
{
	while (ft_iswhitespace(lexer->c) && lexer->c != '\n')
		lexer_advance(lexer);
}

/**
 * Moves the lexer(language interpreter) to the next character in the 
 * shell command given at the prompt
 *
 * @param lexer The lexer to advance
 */
void	lexer_advance(t_lexer_T *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		lexer->i++;
		lexer->c = lexer->src[lexer->i];
	}
}

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
