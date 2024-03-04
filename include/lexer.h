/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:06:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/04 10:00:26 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_lexer_T	*init_lexer(char *src);
void		lexer_advance(t_lexer_T *lexer);
char		lexer_peek(t_lexer_T *lexer, int offset);
t_token_T	*lexer_advance_with(t_lexer_T *lexer, t_token_T *token);
t_token_T	*lexer_advance_current(t_lexer_T *lexer, int type);
void		lexer_skip_whitespace(t_lexer_T *lexer);
t_token_T	*lexer_parse_word(t_lexer_T *lexer);
t_token_T	*lexer_parse_variable(t_lexer_T *lexer);                                
t_token_T	*lexer_parse_number(t_lexer_T *lexer);
t_token_T	*lexer_scan_token(t_lexer_T *lexer);

int			is_valid_variable_char(char c);

//t_token_T	*handle_word_token(t_lexer_T *lexer);
//t_token_T	*handle_name_token(t_lexer_T *lexer);
t_token_T	*handle_word_token(t_lexer_T *lexer);
t_token_T	*handle_number_token(t_lexer_T *lexer);
t_token_T	*handle_variable_token(t_lexer_T *lexer);
t_token_T	*handle_pipe_token(t_lexer_T *lexer);
t_token_T	*handle_redirect_out_token(t_lexer_T *lexer);
t_token_T	*handle_redirect_out_token(t_lexer_T *lexer);
t_token_T	*handle_append_out_token(t_lexer_T *lexer);
t_token_T	*handle_redirect_in_token(t_lexer_T *lexer);
t_token_T	*handle_heredoc_token(t_lexer_T *lexer);
void		handle_unexpected_character(t_lexer_T *lexer);

t_token_T	*handle_expected_tokens(t_lexer_T *lexer);
t_token_T	*handle_redirect_tokens(t_lexer_T *lexer);
t_token_T	*handle_quoted_strings(t_lexer_T *lexer);
t_token_T	*lexer_parse_quoted_string(t_lexer_T *lexer);
t_token_T	*lexer_parse_double_quoted_string(t_lexer_T *lexer);

#endif