/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:49:03 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/01 07:32:42 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

void	run_cmd(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd);
void	runcmd_here(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd);
int		runcmd_pipe(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd);
int		fork1(void);
bool	is_directory(char *path);

/*----------------------------- PIPEX Functions -----------------------------*/

int		ft_execute(char **argv, char **envp);
char	*ft_get_path(char *cmd, char **envp);
void	ft_error(char *str);
void	ft_free(char *path, char **cmd);
void	ft_check_arg(int argc, char **argv);

#endif
