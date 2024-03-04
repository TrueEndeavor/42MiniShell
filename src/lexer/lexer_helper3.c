/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:30 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/04 10:31:29 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*handle_expected_tokens(t_lexer_T *lexer)
{
/* 	// Names start with alphabets or _
	if (ft_isalpha(lexer->c) || (lexer->c == '_'))
		return (handle_word_token(lexer, IS_NOT_A_VARIABLE, \
									IS_A_POSSIBLE_NAME)); */
	// To find if it is a variable - starts with a $ followed by a name
/*	if (lexer->c == '$')
		return (handle_word_token(lexer, IS_A_VARIABLE, \
									IS_A_POSSIBLE_NAME));	*/	
	if (lexer->c == '$')
	{
		if (is_valid_variable_char(lexer_peek(lexer, 1)))
			return (handle_variable_token(lexer));
		return (NULL);
	}
	if (ft_isprint(lexer->c) && (!ft_iswhitespace(lexer->c)))
 	/* if (ft_isalpha(lexer->c) || ft_isdigit(lexer->c) || \
		(lexer->c == '_') || (lexer->c == '-') || \
		(lexer->c == '/') || (lexer->c == '.')) */
		return (handle_word_token(lexer));
	if (ft_isdigit(lexer->c))
		return (lexer_advance_with(lexer, lexer_parse_number(lexer)));
	return (NULL);

}

t_token_T	*handle_redirect_tokens(t_lexer_T *lexer)
{
	if (lexer->c == '>')
	{
		if (lexer_peek(lexer, 1) == '>')
			return (handle_append_out_token(lexer));
		return (lexer_advance_current(lexer, T_REDIRECT_OUT));
	}
	if (lexer->c == '<')
	{
		if (lexer_peek(lexer, 1) == '<')
			return (handle_heredoc_token(lexer));
		return (handle_redirect_in_token(lexer));
	}
	return (NULL);
}


t_token_T	*handle_quoted_strings(t_lexer_T *lexer)
{
	if (lexer->c == '\'')
		return (lexer_advance_with(lexer, lexer_parse_quoted_string(lexer)));
	if (lexer->c == '\"')
		return (lexer_advance_with(lexer, lexer_parse_double_quoted_string(lexer)));
	return (NULL);
}

t_token_T	*lexer_parse_quoted_string(t_lexer_T *lexer)
{
	char		*value;
	char		*new_value;
	int			new_size;
	t_token_T	*ret_token;

	ret_token = NULL;
	value = ft_calloc(2, sizeof(char));
	value[0] = '\'';
	value[1] = '\0';
	lexer_advance(lexer);
	while ((lexer->c != 39) && (lexer_peek(lexer, 1) != ' '))
	{
		if (lexer->c == '\0')
			panic("end of line reached before quote finished");
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		lexer_advance(lexer);
	}
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		lexer_advance(lexer);
	ret_token = init_token(value, T_QUOTED_STRING);
	return (ret_token);
}

t_token_T	*lexer_parse_double_quoted_string(t_lexer_T *lexer)
{
	char		*value;
	char		*new_value;
	int			new_size;
	t_token_T	*ret_token;

	ret_token = NULL;
	value = ft_calloc(2, sizeof(char));
	value[0] = '\"';
	value[1] = '\0';
	lexer_advance(lexer);
	while ((lexer->c != 34) && (lexer_peek(lexer, 1) != ' '))
	{
		if (lexer->c == '\0')
			panic("end of line reached before quote finished");
		new_size = ft_strlen(value) + 2;
		new_value = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(new_value, value, new_size);
		value[new_size - 2] = lexer->c;
		value[new_size - 1] = '\0';
		lexer_advance(lexer);
	}
	new_size = ft_strlen(value) + 2;
	new_value = ft_calloc(new_size, sizeof(char));
	ft_strlcpy(new_value, value, new_size);
	value[new_size - 2] = lexer->c;
	value[new_size - 1] = '\0';
	lexer_advance(lexer);
	ret_token = init_token(value, T_DOUBLE_QUOTED_STRING);
	return (ret_token);
}
