/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:49:22 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/07 18:23:52 by lannur-s         ###   ########.fr       */
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
	char				*src;
	size_t				src_size;
	char				c;
	unsigned int		i;
}	t_lexer_T;

typedef struct PARSER_STRUCT
{
	struct LEXER_STRUCT	*lexer;
	struct TOKEN_STRUCT	*token_head;

}	t_parser_P;

typedef enum PARSED_CMD_ENUM
{
	EXEC_CMD,
	REDIR_CMD,
	PIPE_CMD
}	t_parsed_cmd_E;


typedef struct CMD
{
	int					type;
}	t_cmd_P;

# define MAXARGS 10

typedef struct EXECCMD
{
	int					type;
	char				*argv[MAXARGS];
	char				*eargv[MAXARGS];
}	t_execcmd_P;

typedef struct REDIRCMD
{
	int					type;
	struct CMD			*cmd;
	char				*file;
	char				*efile;
	int					mode;
	int					fd;
}	t_redircmd_P;

typedef struct PIPECMD
{
	int					type;
	struct CMD			*left;
	struct CMD			*right;
}	t_pipecmd_P;

#endif