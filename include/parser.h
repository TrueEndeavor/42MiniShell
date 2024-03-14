/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:06:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/14 09:42:45 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int    syntax_analyzer(t_token_T *current_token);

t_cmd_P	*parse_cmd(t_core_struct *core);
t_cmd_P* parse_pipe(t_core_struct *core);

t_cmd_P	*create_execcmd(void);
t_cmd_P	*create_redircmd(t_cmd_P *subcmd, char *file, int mode, int fd);
t_cmd_P	*create_pipecmd(t_cmd_P *left, t_cmd_P *right);
t_cmd_P	*create_herecmd(t_cmd_P *subcmd, char *limiter);

void	set_write_into(t_redircmd_P *cmd, int writable);
void	set_read_from(t_redircmd_P *cmd, int readable);

void print_cmd(t_cmd_P *cmd);

char    *quote_string(char **str, t_core_struct *core);
char    *free_quotes(char **str, char **name, char **var);
char    *duplicate(const char *src);
char    *ft_expand(t_core_struct *core, char **file_name);




#endif