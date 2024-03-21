/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:30 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/21 12:32:36 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_quotes(char **value, int new_size, t_lexer_T *lexer, char c)
{
	char *copy;

	while (lexer->c != c)
	{
		if (lexer->c == '\0')
		{
			printf ("end of line reached before quote finished\n");
			return (1);
		}
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
	return (0);
}

t_token_T	*handle_quoted_strings(t_lexer_T *lexer)
{
	if (lexer->c == '\'')
		return (lexer_parse_quoted_string(lexer));
	if (lexer->c == '\"')
		return (lexer_parse_double_quoted_string(lexer));
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
		printf ("oh heck\n");
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
	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	lexer_advance(lexer);
	if (ft_get_quotes(&value, new_size, lexer, '\"') == 1)
	{
		printf ("oh heck\n");
		free(value);
		return (NULL);
	}
	lexer_advance(lexer);
	ret_token = init_token(value, T_DOUBLE_QUOTED_STRING);
	return (ret_token);
}
