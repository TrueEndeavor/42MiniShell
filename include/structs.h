/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:49:22 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/05 21:44:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum TOKEN_TYPE_ENUM
{
	WORD,
	NAME,
	ASSIGNMENT_WORD,
	IO_NUMBER,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND_OUT,
	LINEBREAK
}	t_token_type_E;

typedef struct TOKEN_STRUCT
{
	char				*value;
	t_token_type_E		type;
	struct TOKEN_STRUCT	*next;
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