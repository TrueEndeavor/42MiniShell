/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:06:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/19 15:23:44 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

t_cmd_P* parse_pipe(t_token_T	**token);

t_cmd_P	*create_execcmd(void);
t_cmd_P	*create_redircmd(t_cmd_P *subcmd, char *file, int mode, int fd);
t_cmd_P	*create_pipecmd(t_cmd_P *left, t_cmd_P *right);

void print_cmd(t_cmd_P *cmd);

#endif