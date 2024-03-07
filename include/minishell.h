/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:16:04 by lannur-s          #+#    #+#             */
/*   Updated: 2024/03/07 11:28:56 by lannur-s         ###   ########.fr       */
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
 * Flag "g_exit_code" takes in the signum/exit code
 *       = 2 // SIGNINT
 *       = exit code
 */
extern int g_exit_code;

int		display_error(char *str);
void	panic(char *str);


#endif