/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:03:48 by lannur-s          #+#    #+#             */
/*   Updated: 2024/01/25 15:30:14 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum TOKEN_TYPE_ENUM
{
	TOKEN_ID,
	TOKEN_INT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_EOF,
}	t_token_type_E;

	/*TOKEN_CTRL_C,
	TOKEN_CTRL_D,
	TOKEN_CTRL_BACKSLASH,
	TOKEN_ECHO,
	TOKEN_CD,
	TOKEN_PWD,
	TOKEN_EXPORT,
	TOKEN_UNSET,
	TOKEN_ENV,
	TOKEN_EXIT */

typedef struct TOKEN_STRUCT
{
	char			*value;
	t_token_type_E	type;
}	t_token_T;

t_token_T	*init_token(char *value, int type);
char		*token_type_to_str(int type);
char		*token_to_str(t_token_T *token);

#endif