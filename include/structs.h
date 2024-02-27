/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:49:22 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/27 11:06:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MAXARGS 10

# define IS_A_VARIABLE 1
# define IS_NOT_A_VARIABLE 0

# define IS_A_POSSIBLE_NAME 1
# define IS_NOT_A_POSSIBLE_NAME 0

/*---------------------- Structures for Lexer & Token  ----------------------*/
typedef enum TOKEN_TYPE_ENUM
{
	T_START = 0,
	T_WORD = 1,
	T_NAME = 2,
	T_VARIABLE = 3,	
	T_ASSIGNMENT_WORD  = 4,
	T_IO_NUMBER = 5,
	T_DOLLAR = 6,	
	T_PIPE = 7,
	T_REDIRECT_IN = 8,
	T_REDIRECT_OUT = 9,
	T_HEREDOC = 10,
	T_APPEND_OUT = 11,
	T_LINEBREAK = 12,
	T_QUOTED_STRING = 13,
	T_DOUBLE_QUOTED_STRING = 14	
}	t_token_type_E;

typedef struct TOKEN_STRUCT
{
	int					type;
	char				*value;
	struct TOKEN_STRUCT	*next;
}	t_token_T;

typedef struct LEXER_STRUCT
{
	char				*src;
	size_t				src_size;
	char				c;
	unsigned int		i;
}	t_lexer_T;

/*---------------------- Structures for Parser  ----------------------*/
typedef enum PARSER_CMD_ENUM
{
	EXEC_CMD = 1,
	REDIR_CMD = 2,
	PIPE_CMD = 3
}	t_parser_cmd_E;

/* Base structure */
typedef struct CMD
{
	t_parser_cmd_E		type;
}	t_cmd_P;

/* Derived structures */
typedef struct EXECCMD
{
	int					type;
	char				*argv[MAXARGS];
}	t_execcmd_P;

typedef struct REDIRCMD
{
	int					type;
	struct CMD			*cmd;
	char				*file;
	int					mode;
	int					fd;
	int					permission;
	int					read_from;		
	int					write_into;	
}	t_redircmd_P;

typedef struct PIPECMD
{
	int					type;
	struct CMD			*left;
	struct CMD			*right;
}	t_pipecmd_P;

/*---------------------- Structures for Minishell  ----------------------*/
typedef struct ENVLIST
{
	char				*name;
	char				*value;	
	struct ENVLIST		*next;
}	t_env_list;

typedef struct CORESTRUCT
{
	t_env_list				*env_list;
}	t_core_struct;


#endif