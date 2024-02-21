/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:48:35 by lannur-s          #+#    #+#             */
/*   Updated: 2024/01/24 16:49:34 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		match_builtin(t_cmd_P *root, t_core_struct *general);

int		exec_cd(t_core_struct *general);
int		exec_echo(t_core_struct *general);
int		exec_env(t_core_struct *general);
int		exec_exit(t_core_struct *general);
int		exec_export(t_core_struct *general);
int		exec_pwd(t_core_struct *general);
int		exec_unset(t_core_struct *general);

#endif