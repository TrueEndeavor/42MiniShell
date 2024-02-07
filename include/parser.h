/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:30:58 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/07 18:45:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_parser_P	init_parser(t_lexer_T *lexer);
t_token_T	parser_eat(t_parser_P *parser, int type);

// Node Constructors
t_cmd_P		*create_execcmd(void);
t_cmd_P		*create_redircmd(t_cmd_P *subcmd, char *file, int mode, int fd);
t_cmd_P		*create_pipecmd(t_cmd_P *left, t_cmd_P *right);


#endif