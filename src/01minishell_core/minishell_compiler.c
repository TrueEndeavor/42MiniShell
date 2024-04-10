/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_compiler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:09:13 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 14:14:51 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*initialize_lexer_and_first_token(char *prompt, t_lexer_T **lxr_ptr)
{
	t_lexer_T	*lexer;
	t_token_T	*tok;

	lexer = init_lexer(prompt);
	if (!lexer)
		return (NULL);
	*lxr_ptr = lexer;
	tok = lexer_scan_token(lexer);
	if (tok == NULL)
	{
		free(*lxr_ptr);
		return (NULL);
	}
	if (!tok || tok->type == T_LINEBREAK)
	{
		free(lexer);
		return (NULL);
	}
	return (tok);
}

t_token_T	*add_token_to_list(t_token_T **prev_tok_ptr, t_token_T **tok_ptr, \
							t_lexer_T **lexer_ptr, t_token_T **token_head_ptr)
{
	t_token_T	*prev_tok;
	t_token_T	*tok;

	prev_tok = *prev_tok_ptr;
	tok = *tok_ptr;
	if (prev_tok != NULL)
		prev_tok->next = tok;
	*prev_tok_ptr = tok;
	*tok_ptr = lexer_scan_token(*lexer_ptr);
	if (*tok_ptr == NULL)
	{
		free(*lexer_ptr);
		ft_free_tok_list(token_head_ptr);
		return (NULL);
	}
	(*tok_ptr)->next = NULL;
	return (*tok_ptr);
}

t_token_T	*minishell_compile(char *prompt)
{
	t_lexer_T	*lexer;
	t_token_T	*token_head;
	t_token_T	*tok;
	t_token_T	*prev_tok;

	prev_tok = NULL;
	tok = initialize_lexer_and_first_token(prompt, &lexer);
	if (tok == NULL)
		return (NULL);
	token_head = tok;
	while (tok->type != T_LINEBREAK)
	{
		if (prev_tok != NULL)
			prev_tok->next = tok;
		tok = add_token_to_list(&prev_tok, &tok, &lexer, &token_head);
		if (!tok)
		{
			return (NULL);
		}
	}
	prev_tok->next = tok;
	tok->next = NULL;
	free(lexer);
	return (token_head);
}
