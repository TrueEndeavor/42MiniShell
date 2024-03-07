/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:49:03 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/07 12:26:18 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "structs.h"

void	run_cmd(t_cmd_P *cmd, t_core_struct *core);
int		fork1(void);

/*----------------------------- PIPEX Functions -----------------------------*/

int 	ft_execute(char **argv, char **envp);
char	*ft_get_path(char *cmd, char **envp);
void	ft_error(char *str);
void	ft_free(char *path, char **cmd);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_check_arg(int argc, char **argv);


#endif
