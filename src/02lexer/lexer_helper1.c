/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:20:12 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 11:41:48 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*handle_word_token(t_lexer_T *lexer)
{
	return (lexer_parse_word(lexer));
}

t_token_T	*handle_expected_tokens(t_lexer_T *lexer)
{
	if (ft_isprint(lexer->c) && (!ft_iswhitespace(lexer->c)))
		return (handle_word_token(lexer));
	return (NULL);
}

void	handle_unexpected_character(t_lexer_T *lexer)
{
	printf("[Lexer]: Unexpected character '%c'\n", lexer->c);
}
