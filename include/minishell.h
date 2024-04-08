/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:16:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/08 11:57:31 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h> //For exact error no ENOTDIR or EACCES
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "expand.h"
# include "builtins.h"
# include "utils.h"
# include "signals.h"

# define DEBUG 0

/* 
 * Flag "g_signum" takes in the signum/exit code
 *       = 2 //SIGNINT
 *       = 3 //SIGQUIT
 */
extern int	g_signum;

int			display_new_prompt(t_core_struct *core);
t_token_T	*minishell_compile(char *src);
int			process_signals_in_child(int status);
void		process_eof(t_core_struct *core);

int			display_error(char *str);
void		panic(char *str);
void		ft_free_tok_list(t_token_T **token_head);
void		ft_free_env(t_env_list *env);
void		ft_free_cmd(t_cmd_P *cmd);
void		ft_free_heredoc(t_cmd_P *cmd);


#endif