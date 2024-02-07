/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:25:00 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/07 18:43:26 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_P	init_parser(t_lexer_T *lexer)
{
	t_parser_P	*parser;

	parser = ft_calloc(1, sizeof(t_parser_P));
	parser->lexer = lexer;
	parser->token = lexer_scan_token(lexer);
}

t_token_T	parser_eat(t_parser_P *parser, int type)
{
	if (parser->token->type != type)
	{
		printf("[Parser]: Unexpected token: '%s' was expecting : '%s' \n", \
			token_to_str(parser->token), token_type_to_str(type));
		exit (1);
	}
	parser->token = lexer_scan_token(lexer);
	return (parser->token);
}
