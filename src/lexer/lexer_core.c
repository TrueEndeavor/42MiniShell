/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:04:53 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/21 11:18:57 by trysinsk         ###   ########.fr       */
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
	while (ft_iswhitespace(lexer->c))
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

void	handle_unexpected_character(t_lexer_T *lexer)
{
	printf("[Lexer]: Unexpected character '%c'\n", lexer->c);
}
