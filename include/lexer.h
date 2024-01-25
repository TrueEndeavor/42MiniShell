/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:06:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/01/25 15:24:22 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct LEXER_STRUCT
{
	char			*src;
	size_t			src_size;
	char			c;
	unsigned int	i;
}	t_lexer_T;

t_lexer_T		*init_lexer(char *src);
void			lexer_advance(t_lexer_T *lexer);
char			lexer_peek(t_lexer_T *lexer, int offset);
t_token_T		*lexer_advance_with(t_lexer_T *lexer, t_token_T *token);
t_token_T		*lexer_advance_current(t_lexer_T *lexer, int type);
void			lexer_skip_whitespace(t_lexer_T *lexer);
t_token_T		*lexer_parse_id(t_lexer_T *lexer);
t_token_T		*lexer_parse_number(t_lexer_T *lexer);
t_token_T		*lexer_next_token(t_lexer_T *lexer);

t_token_T		*handle_alphabet_token(t_lexer_T *lexer);
t_token_T		*handle_number_token(t_lexer_T *lexer);
t_token_T		*handle_pipe_token(t_lexer_T *lexer);
t_token_T		*handle_redirect_out_token(t_lexer_T *lexer);
t_token_T		*handle_redirect_out_token(t_lexer_T *lexer);
t_token_T		*handle_append_out_token(t_lexer_T *lexer);
t_token_T		*handle_redirect_in_token(t_lexer_T *lexer);
t_token_T		*handle_heredoc_token(t_lexer_T *lexer);
void			handle_unexpected_character(t_lexer_T *lexer);

t_token_T		*handle_expected_tokens(t_lexer_T *lexer);
t_token_T		*handle_redirect_tokens(t_lexer_T *lexer);

#endif