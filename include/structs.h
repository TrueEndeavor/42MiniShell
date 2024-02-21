/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:49:22 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/21 16:36:05 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MAXARGS 10

/*---------------------- Structures for Lexer & Token  ----------------------*/
typedef enum TOKEN_TYPE_ENUM
{
	T_START = 0,
	T_WORD = 1,
	T_NAME,
	T_ASSIGNMENT_WORD,
	T_IO_NUMBER,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HEREDOC,
	T_APPEND_OUT,
	T_LINEBREAK
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
typedef struct CORESTRUCT
{
	char				**envp;
}	t_core_struct;

#endif