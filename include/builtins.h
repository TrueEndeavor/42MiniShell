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

int		cd_builtin(t_core_struct *core);
int		echo_builtin(t_core_struct *core);
int		env_builtin(t_core_struct *core);
int		exitv(t_core_struct *core);
int	    export_builtin(t_execcmd_P *ecmd, t_core_struct *core);
int		pwd_builtin(t_core_struct *core);
int		unset_builtin(t_core_struct *core);

#endif