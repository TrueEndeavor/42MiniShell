/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:30 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 13:25:04 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_quotes(char **value, int new_size, t_lexer_T *lexer, char c)
{
	char	*copy;
	int		num_dq;
	int		num_sq;

	num_sq = 0;
	num_dq = 0;
	while (lexer->c != '\0')
	{
		printf("current lexer->c: %c\n", lexer->c);
		if (lexer->c == c)
			num_dq ++;
		if (lexer->c == '\'')
			num_sq ++;
		if (lexer->c == c && lexer_peek(lexer, 1) == ' ')
			break ;
		new_size = ft_strlen((*value)) + 2;
		copy = ft_calloc(new_size, sizeof(char));
		ft_strlcpy(copy, (*value), new_size);
		free(*value);
		(*value) = ft_calloc(new_size, sizeof(char));
		ft_strlcpy((*value), copy, new_size);
		(*value)[new_size - 2] = lexer->c;
		(*value)[new_size - 1] = '\0';
		free(copy);
		lexer_advance(lexer);
	}
	if (!is_nested_quotes(*value))
		return (1);
	/*if ((num_dq % 2 == 1) || (num_sq % 2 == 1))
		return (1);*/
	return (0);
}

t_token_T	*handle_quoted_strings(t_lexer_T *lexer)
{
	if (lexer->c == '\'')
		return (lexer_parse_quoted_string(lexer));
	if (lexer->c == '\"')
		return (lexer_parse_double_quoted_string(lexer));
		//return (extract_quoted_string(lexer));
	return (NULL);
}

t_token_T	*lexer_parse_quoted_string(t_lexer_T *lexer)
{
	char		*value;
	int			new_size;
	t_token_T	*ret_token;

	ret_token = NULL;
	new_size = 0;
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	lexer_advance(lexer);
	if (ft_get_quotes(&value, new_size, lexer, '\'') == 1)
	{
		printf ("end of statement reached before closing quote\n");
		free(value);
		return (NULL);
	}
	lexer_advance(lexer);
	ret_token = init_token(value, T_QUOTED_STRING);
	return (ret_token);
}

t_token_T	*lexer_parse_double_quoted_string(t_lexer_T *lexer)
{
	char		*value;
	int			new_size;
	t_token_T	*ret_token;

	ret_token = NULL;
	new_size = 0;
	//value = ft_calloc(2, sizeof(char));
	value = ft_calloc(1, sizeof(char));
	//value[0] = '\"';
	value[1] = '\0';
	//lexer_advance(lexer);
	if (ft_get_quotes(&value, new_size, lexer, '\"') == 1)
	{
		printf ("end of statement reached before closing quote\n");
		free(value);
		return (NULL);
	}
	lexer_advance(lexer);
	ret_token = init_token(value, T_DOUBLE_QUOTED_STRING);
	return (ret_token);
}
