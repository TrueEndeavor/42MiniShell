/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:49:22 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/02 20:09:55 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum TOKEN_TYPE_ENUM
{
	WORD,
	VARIABLE,
	IO_NUMBER,
	ASSIGNMENT_WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND_OUT,
	DOUBLE_QUOTED_STRING,
	LINEBREAK
}	t_token_type_E;

typedef struct TOKEN_STRUCT
{
	char			*value;
	t_token_type_E	type;
}	t_token_T;

typedef struct LEXER_STRUCT
{
	char			*src;
	size_t			src_size;
	char			c;
	unsigned int	i;
}	t_lexer_T;

typedef struct PARSER_STRUCT
{
	t_lexer_T	*lexer;
	t_token_T	*token;

}	t_parser_T;

#endif