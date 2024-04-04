/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:49:03 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/04 14:32:42 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

void	run_cmd(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd);
void	run_here(t_herecmd_P *hcmd, t_core_struct *core, int fd, t_cmd_P *fcmd);
void    handle_heredoc(t_core_struct *core, t_cmd_P *root);
int		runcmd_pipe(t_cmd_P *cmd, t_core_struct *core, t_cmd_P *fcmd);
pid_t	fork1(void);
bool	is_directory(char *path);

/*----------------------------- PIPEX Functions -----------------------------*/

int		ft_execute(char **argv, char **envp);
char	*ft_get_path(char *cmd, char **envp);
void	ft_free(char *path, char **cmd);

#endif
