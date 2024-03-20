/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:06:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/20 17:31:15 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

bool			syntax_analyzer(t_core_struct *core);
t_state_enum	transition_q0(t_state_enum state, t_token_type_E token_type);
t_state_enum	transition_q1(t_state_enum state, t_token_type_E token_type);
t_state_enum	transition_q2(t_state_enum state, t_token_type_E token_type);
t_state_enum	transition_q3(t_state_enum state, t_token_type_E token_type);

t_cmd_P			*parse_cmd(t_core_struct *core);
t_cmd_P			*parse_pipe(t_core_struct *core);

t_cmd_P			*create_execcmd(void);
t_cmd_P			*create_redircmd(t_cmd_P *subcmd, char *file, int mode, int fd);
t_cmd_P			*create_pipecmd(t_cmd_P *left, t_cmd_P *right);
t_cmd_P			*create_herecmd(t_cmd_P *subcmd, char *limiter);

void			set_write_into(t_redircmd_P *cmd, int writable);
void			set_read_from(t_redircmd_P *cmd, int readable);

void			print_cmd(t_cmd_P *cmd);

int             ft_slen(const char *str);
char			*quote_string(char **str, t_core_struct *core, int var_count, int _var);
char			*free_quotes(char **str, char **name, char **var);
char			*dupl(const char *src);
char			*ft_expand(t_core_struct *core, char **file_name);
char			*ft_here(char **value);
void			ft_initialize_tab(char **name, char **var);
bool			is_assignment_word(char *str);

t_token_T       *search_for(t_token_T *current, int target_token_type);
t_token_T	    *peek_next_token(t_token_T *current_token);
t_token_T	    *advance_token(t_token_T **current_token);

void            ft_loop_quote(t_core_struct *core);
void            ft_loop_variable(t_core_struct *core);
void            ft_fill_exec(t_core_struct *core, int *argc, t_execcmd_P *cmd);

t_cmd_P         *ft_r_in(t_core_struct *core, t_cmd_P **cmd, t_token_T *next_tolkien);
t_cmd_P         *ft_r_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *next_tolkien);
t_cmd_P         *ft_app_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *next_tolkien);
t_cmd_P         *ft_cr_here(t_core_struct *core, t_cmd_P **cmd, t_token_T *next_tolkien);


#endif