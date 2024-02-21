/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:16:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/21 13:59:17 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "libft.h"
# include "utils.h"
# include "dev.h"

int		display_error(char *str);
void	panic(char *str);

t_cmd_P	*parse_cmd(t_token_T **token_list);
void	run_cmd(t_cmd_P *cmd, t_general *general);
int match_builtin(t_cmd_P *root, t_general *general);


/*------------
PIPEX
------------*/

void	ft_execute(char **argv, char **envp);
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