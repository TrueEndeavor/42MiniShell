/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:06:15 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/28 14:04:34 by trysinsk         ###   ########.fr       */
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

int				check_num_arg(char *str);
int				ft_slen(const char *str);
char			*quote(char **s, t_core_struct *co, int var_c, int i);
char			*free_quotes(char **str, char **name, char **var);
char			*dupl(const char *src);
char			*ft_expand(t_core_struct *core, char **str);
char			*ft_here(char **value);
void			ft_initialize_tab(char **name, char **var, int size);
bool			is_assignment_word(char *str);

t_token_T		*search_for(t_token_T *current, int target_token_type);
t_token_T		*peek_next_token(t_token_T *current_token);
t_token_T		*advance_token(t_token_T **current_token);

void			ft_loop_assign(t_core_struct *core);
void			ft_loop_quote(t_core_struct *c);
void			ft_loop_variable(t_core_struct *core);
void			ft_fill_exec(t_core_struct *core, int *argc, t_execcmd_P *cmd);

t_cmd_P			*ft_r_in(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok);
t_cmd_P			*ft_r_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok);
t_cmd_P			*ft_app_out(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok);
t_cmd_P			*ft_cr_here(t_core_struct *core, t_cmd_P **cmd, t_token_T *tok);
int				check_redir(t_core_struct *core);

#endif
