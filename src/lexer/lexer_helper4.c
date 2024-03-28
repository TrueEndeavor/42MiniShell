/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:21:28 by trysinsk          #+#    #+#             */
/*   Updated: 2024/03/28 13:16:59 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_T	*extract_quoted_string(t_lexer_T *lexer)
{
	int		start_position;
	int		end_position;
	int		in_quote;
	int		nesting_level;
	char	*value;
	size_t	sz;
	//char *beginning;
	//char *ending;

	start_position = 0;
	end_position = 0;
	in_quote = 0;
	nesting_level = 0;
	while (lexer->c)
	{
		printf("char=%c\n", lexer->c);
		if (lexer->c == '"' && !in_quote)
		{
			printf("start_position = %d\n", start_position);
			lexer_advance(lexer);
			//beginning = (lexer->src) + (lexer->i);
			start_position = lexer->i;
			in_quote = 1;
		}
		else if (lexer->c == '"' && in_quote)
		{
			if (nesting_level == 0)
			{
				//ending = (lexer->src) + (lexer->i);
				end_position = lexer->i;
				printf ("end_position = %d\n", end_position);
				sz = (end_position - start_position);
				printf ("sz=%ld\n", sz);
				value = ft_substr(lexer->src, start_position, sz);
				lexer_advance(lexer);
				printf("value=%s\n", value);
				return (init_token(value, T_DQ_STRING));
			}
			else
				nesting_level--;
		}
		else if (lexer->c == '"' && !in_quote)
		{
			nesting_level++;
		}
		// check for nesting_level=0 finally, otherwise syntax error
		lexer_advance(lexer);
	}
	return (NULL);
}
