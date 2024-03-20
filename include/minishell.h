/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:16:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/20 13:38:52 by trysinsk         ###   ########.fr       */
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
# include "builtins.h"
# include "utils.h"
# include "dev.h"
# include "signals.h"

/* 
 * Flag "g_signum" takes in the signum/exit code
 *       = 2 //SIGNINT
 *       = 3 //SIGQUIT
 */
extern int	g_signum;

int			display_error(char *str);
void		panic(char *str);
void		ft_free_tok_list(t_token_T **token_head);
void		ft_free_env(t_env_list *env);
void		ft_free_cmd(t_cmd_P *cmd);
int			is_valid_variable_char(char c);
bool		is_valid_variable_name(char *name);
void		ft_update_shlvl(t_core_struct *core);

#endif