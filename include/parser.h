/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:30:58 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/09 10:55:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_parser_P	*init_parser(t_lexer_T *lexer);
t_token_T	*parser_eat(t_parser_P *parser, t_token_type_E type);
t_AST_P		*parser_parse(t_parser_P *parser);
t_AST_P		*parser_parse_compound(t_parser_P *parser);


// Node Constructors
t_cmd_P		*create_execcmd(void);
t_cmd_P		*create_redircmd(t_cmd_P *subcmd, char *file, int mode, int fd);
t_cmd_P		*create_pipecmd(t_cmd_P *left, t_cmd_P *right);


#endif