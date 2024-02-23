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

int		match_builtin(t_cmd_P *root, t_core_struct *core);

int		builtin_cd(t_execcmd_P *ecmd, t_core_struct *core);
int		builtin_echo(t_execcmd_P *ecmd, t_core_struct *core);
int		builtin_env(t_execcmd_P *ecmd, t_core_struct *core);
int		builtin_exitv(t_execcmd_P *ecmd, t_core_struct *core);
int		builtin_export(t_execcmd_P *ecmd, t_core_struct *core);
int		builtin_pwd(t_execcmd_P *ecmd, t_core_struct *core);
int		builtin_unset(t_execcmd_P *ecmd, t_core_struct *core);

int		count_of_env(char **envp);
void	display_env(int count, char	**envp);

#endif