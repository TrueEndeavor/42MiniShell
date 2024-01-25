/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:38:43 by lannur-s          #+#    #+#             */
/*   Updated: 2024/01/25 15:19:21 by lannur-s         ###   ########.fr       */
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

t_token_T	*handle_heredoc_token(t_lexer_T *lexer)
{
	return (lexer_advance_with(lexer, init_token("<<", TOKEN_HEREDOC)));
}

t_token_T	*handle_redirect_in_token(t_lexer_T *lexer)
{
	return (lexer_advance_current(lexer, TOKEN_REDIRECT_IN));
}

void	handle_unexpected_character(t_lexer_T *lexer)
{
	printf("[Lexer]: Unexpected character '%c'\n", lexer->c);
}
