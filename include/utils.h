/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:48:35 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 09:58:21 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int			min_int(int a, int b);
int			is_valid_variable_char(char c);
bool		is_valid_variable_name(char *name);
void		ft_update_shlvl(t_core_struct *core);
t_env_list	*create_dummy_env(void);
int			is_all_whitespace(char *str);
bool		check_for_exit_code(int exit_code, int signum);

#endif
